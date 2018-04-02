#include <algorithm>
#include "caffe/layer.hpp"
#include "caffe/deep_hand_model_layers.hpp"
namespace caffe {

    template <typename Dtype>
    void DeepHandModelPinholeCameraLayer<Dtype>::LayerSetUp(const vector<Blob<Dtype>*>& bottom,
        const vector<Blob<Dtype>*>& top) {
    }

    template <typename Dtype>
    void DeepHandModelPinholeCameraLayer<Dtype>::Reshape(const vector<Blob<Dtype>*>& bottom,
        const vector<Blob<Dtype>*>& top) {
        const int axis = bottom[0]->CanonicalAxisIndex(
            this->layer_param_.inner_product_param().axis());
        vector<int> top_shape = bottom[0]->shape();
        top_shape.resize(axis + 1);
        top_shape[axis] = JointNum * 2;
        top[0]->Reshape(top_shape);
    }

    template <typename Dtype>
    void DeepHandModelPinholeCameraLayer<Dtype>::Forward_cpu(const vector<Blob<Dtype>*>& bottom,
        const vector<Blob<Dtype>*>& top) {
        const Dtype* bottom_data = bottom[0]->cpu_data();
        Dtype* top_data = top[0]->mutable_cpu_data();
        const int batSize = (bottom[0]->shape())[0];
        for (int t = 0; t < batSize; t++) {
            for (int i = 0; i < JointNum; i++) {
                int Tid = t * JointNum * 2 + i * 2, Bid = t * JointNum * 3 + i * 3;
                double x = bottom_data[Bid], y = bottom_data[Bid + 1], z = bottom_data[Bid + 2];
                top_data[Tid] = (x + 1) / 2.0;
                top_data[Tid + 1] = (-y + 1) / 2.0;
            }
        }
    }


    template <typename Dtype>
    void DeepHandModelPinholeCameraLayer<Dtype>::Backward_cpu(const vector<Blob<Dtype>*>& top,
        const vector<bool>& propagate_down,
        const vector<Blob<Dtype>*>& bottom) {

        const Dtype* bottom_data = bottom[0]->cpu_data();
        const Dtype* top_diff = top[0]->cpu_diff();
        Dtype* bottom_diff = bottom[0]->mutable_cpu_diff();

        const int batSize = (bottom[0]->shape())[0];

        for (int t = 0; t < batSize; t++) {
            for (int i = 0; i < JointNum; i++) {
                int Bid = i * 3, Tid = i * 2;
                double x = bottom_data[Bid], y = bottom_data[Bid + 1], z = bottom_data[Bid + 2];
                bottom_diff[Bid] = top_diff[Tid] * 1.0 / 2.0;
                bottom_diff[Bid + 1] = -top_diff[Tid + 1] * 1.0 / 2.0;
                bottom_diff[Bid + 2] = 0.0;
            }
        }
    }

#ifdef CPU_ONLY
    STUB_GPU(DeepHandModelPinholeCameraLayer);
#endif

    INSTANTIATE_CLASS(DeepHandModelPinholeCameraLayer);
    REGISTER_LAYER_CLASS(DeepHandModelPinholeCamera);
}  // namespace caffe
