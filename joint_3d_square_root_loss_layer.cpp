#include <vector>

#include "caffe/layer.hpp"
#include "caffe/util/io.hpp"
#include "caffe/util/math_functions.hpp"
#include "caffe/operations.hpp"

namespace caffe {

    template <typename Dtype>
    void Joint3DSquareRootLossLayer<Dtype>::LayerSetUp(
        const vector<Blob<Dtype>*>& bottom, const vector<Blob<Dtype>*>& top) {
        if (this->layer_param_.loss_weight_size() == 0) {
            this->layer_param_.add_loss_weight(Dtype(1));
        }
    }


    template <typename Dtype>
    void Joint3DSquareRootLossLayer<Dtype>::Reshape(
        const vector<Blob<Dtype>*>& bottom, const vector<Blob<Dtype>*>& top) {
        vector<int> loss_shape(0);
        top[0]->Reshape(loss_shape);
    }

    template <typename Dtype>
    void Joint3DSquareRootLossLayer<Dtype>::Forward_cpu(const vector<Blob<Dtype>*>& bottom,
        const vector<Blob<Dtype>*>& top) {
        int batSize = (bottom[0]->shape())[0];
        const Dtype* bottom_data = bottom[0]->cpu_data();
        const Dtype* label_data = bottom[1]->cpu_data();
        Dtype loss = 0;
        for (int t = 0; t < batSize; t++) 
        {            
            for (int i = 0; i < JointNum; i++) 
            {
                int Bid = t * JointNum * 3 + i * 3;
                Dtype cur_loss = 0.0;
                for (int j = 0; j < 3; j++) cur_loss += ((bottom_data[Bid + j] - label_data[Bid + j]) * (bottom_data[Bid + j] - label_data[Bid + j]));
                cur_loss = sqrt(cur_loss);
                loss += cur_loss;
            }
        }
        top[0]->mutable_cpu_data()[0] = loss / batSize / JointNum;
    }


    template <typename Dtype>
    void Joint3DSquareRootLossLayer<Dtype>::Backward_cpu(const vector<Blob<Dtype>*>& top,
        const vector<bool>& propagate_down, const vector<Blob<Dtype>*>& bottom) {
        int batSize = (bottom[0]->shape())[0];
        const Dtype* bottom_data = bottom[0]->cpu_data();
        const Dtype* label_data = bottom[1]->cpu_data();
        Dtype top_diff = top[0]->cpu_diff()[0] / batSize / JointNum;
        Dtype* bottom_diff = bottom[0]->mutable_cpu_diff();
        if (propagate_down[0]) {
            for (int t = 0; t < batSize; t++) {
                int Bid = t * JointNum * 3;
                for (int i = 0; i < JointNum * 3; i++) bottom_diff[Bid + i] = 0;
                for (int i = 0; i < JointNum; i++) {
                    for (int j = 0; j < 3; j++) {
                        Bid = t * JointNum * 3 + i * 3;
                        bottom_diff[Bid + j] = top_diff * 2 * (bottom_data[Bid + j] - label_data[Bid + j]);
                    }
                }
            }
        }

    }

#ifdef CPU_ONLY
    STUB_GPU(Joint3DSquareRootLossLayer);
#endif

    INSTANTIATE_CLASS(Joint3DSquareRootLossLayer);
    REGISTER_LAYER_CLASS(Joint3DSquareRootLoss);

}  // namespace caffe
