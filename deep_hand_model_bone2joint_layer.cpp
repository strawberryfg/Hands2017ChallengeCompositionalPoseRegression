#include <vector>

#include "caffe/layer.hpp"
#include "caffe/util/io.hpp"
#include "caffe/util/math_functions.hpp"
#include "caffe/deep_hand_model_layers.hpp"

namespace caffe {

    template <typename Dtype>
    void DeepHandModelBone2JointLayer<Dtype>::LayerSetUp(const vector<Blob<Dtype>*>& bottom, const vector<Blob<Dtype>*>& top) 
    {
        for (int i = 0; i < BoneNum; i++) which_bone[bones[i][0]][bones[i][1]] = i;
    }


    template <typename Dtype>
    void DeepHandModelBone2JointLayer<Dtype>::Reshape(const vector<Blob<Dtype>*>& bottom,
        const vector<Blob<Dtype>*>& top) {
        const int axis = bottom[0]->CanonicalAxisIndex(
            this->layer_param_.inner_product_param().axis());
        vector<int> top_shape = bottom[0]->shape();
        top_shape.resize(axis + 1);
        top_shape[axis] = JointNum * 3;
        top[0]->Reshape(top_shape);
    }

    template <typename Dtype>
    void DeepHandModelBone2JointLayer<Dtype>::Forward_cpu(const vector<Blob<Dtype>*>& bottom,
        const vector<Blob<Dtype>*>& top) {
        int batSize = (bottom[0]->shape())[0];
        const Dtype* bottom_data = bottom[0]->cpu_data();
        Dtype* top_data = top[0]->mutable_cpu_data();
        for (int t = 0; t < batSize; t++) {
            int Tid = t * JointNum * 3;
            int Bid = t * BoneNum * 3;
            for (int i = 0; i < JointNum * 3; i++) top_data[Tid + i] = 0.0;
            for (int i = 0; i < JointNum; i++) {
                int x = i;
                while (x != wrist) {
                    int cur_bone = which_bone[x][parent[x]];
                    for (int j = 0; j < 3; j++) {
                        top_data[Tid + i * 3 + j] += -bottom_data[Bid + cur_bone * 3 + j];
                        //the boint is pointing from the current joint towards its parent
                        //so we need to take its opposite number
                    }
                    x = parent[x];
                }
            }
        }
    }

    template <typename Dtype>
    void DeepHandModelBone2JointLayer<Dtype>::Backward_cpu(const vector<Blob<Dtype>*>& top,
        const vector<bool>& propagate_down, const vector<Blob<Dtype>*>& bottom) {
        int batSize = (bottom[0]->shape())[0];
        const Dtype* bottom_data = bottom[0]->cpu_data();
        const Dtype* top_diff = top[0]->cpu_diff();
        Dtype* bottom_diff = bottom[0]->mutable_cpu_diff();
        if (propagate_down[0]) {
            for (int t = 0; t < batSize; t++) {
                int Tid = t * JointNum * 3;
                int Bid = t * BoneNum * 3;
                for (int i = 0; i < BoneNum * 3; i++) bottom_diff[Bid + i] = 0.0;
                for (int i = 0; i < JointNum; i++) {
                    int x = i;
                    while (x != wrist) {
                        int cur_bone = which_bone[x][parent[x]];
                        for (int j = 0; j < 3; j++) {
                            bottom_diff[Bid + cur_bone * 3 + j] += -top_diff[Tid + i * 3 + j];
                        }
                        x = parent[x];
                    }
                }
            }
        }
    }

#ifdef CPU_ONLY
    STUB_GPU(DeepHandModelBone2JointLayer);
#endif

    INSTANTIATE_CLASS(DeepHandModelBone2JointLayer);
    REGISTER_LAYER_CLASS(DeepHandModelBone2Joint);

}  // namespace caffe
