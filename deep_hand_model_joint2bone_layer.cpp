#include <vector>

#include "caffe/layer.hpp"
#include "caffe/util/io.hpp"
#include "caffe/util/math_functions.hpp"
#include "caffe/deep_hand_model_layers.hpp"

namespace caffe {

    template <typename Dtype>
    void DeepHandModelJoint2BoneLayer<Dtype>::LayerSetUp(
        const vector<Blob<Dtype>*>& bottom, const vector<Blob<Dtype>*>& top) {

    }

    template <typename Dtype>
    void DeepHandModelJoint2BoneLayer<Dtype>::Reshape(
        const vector<Blob<Dtype>*>& bottom, const vector<Blob<Dtype>*>& top) {
        const int axis = bottom[0]->CanonicalAxisIndex(
            this->layer_param_.inner_product_param().axis());
        vector<int> top_shape = bottom[0]->shape();
        top_shape.resize(axis + 1);
        top_shape[axis] = BoneNum * 3;
        top[0]->Reshape(top_shape);
    }

    template <typename Dtype>
    void DeepHandModelJoint2BoneLayer<Dtype>::Forward_cpu(const vector<Blob<Dtype>*>& bottom,
        const vector<Blob<Dtype>*>& top) {
        int batSize = (bottom[0]->shape())[0];
        const Dtype* bottom_data = bottom[0]->cpu_data();
        Dtype* top_data = top[0]->mutable_cpu_data();
        for (int t = 0; t < batSize; t++) {
            for (int k = 0; k < BoneNum; k++) {
                int Tid = t * BoneNum * 3;
                int Uid = t * JointNum * 3 + bones[k][0] * 3, Vid = t * JointNum * 3 + bones[k][1] * 3;
                for (int l = 0; l < 3; l++) {
                    top_data[Tid + k * 3 + l] = bottom_data[Vid + l] - bottom_data[Uid + l];
                    //which is pointing from the joint to is parent in the kinematic chain
                }
            }
        }
    }

    template <typename Dtype>
    void DeepHandModelJoint2BoneLayer<Dtype>::Backward_cpu(const vector<Blob<Dtype>*>& top,
        const vector<bool>& propagate_down, const vector<Blob<Dtype>*>& bottom) {
        int batSize = (bottom[0]->shape())[0];
        const Dtype* bottom_data = bottom[0]->cpu_data();
        const Dtype* top_diff = top[0]->cpu_diff();
        Dtype* bottom_diff = bottom[0]->mutable_cpu_diff();
        if (propagate_down[0]) {
            for (int t = 0; t < batSize; t++) {
                int Bid = t * JointNum * 3;
                for (int i = 0; i < JointNum * 3; i++) bottom_diff[Bid + i] = 0.0;
                for (int k = 0; k < BoneNum; k++) {
                    int Tid = t * BoneNum * 3;
                    int u = bones[k][0], v = bones[k][1];
                    int Uid = t * JointNum * 3 + u * 3, Vid = t * JointNum * 3 + v * 3;
                    for (int l = 0; l < 3; l++) {
                        bottom_diff[Vid + l] += top_diff[Tid + k * 3 + l] * 1.0;
                        bottom_diff[Uid + l] += top_diff[Tid + k * 3 + l] * -1.0;
                    }
                }
            }
        }
    }

#ifdef CPU_ONLY
    STUB_GPU(DeepHandModelJoint2BoneLayer);
#endif

    INSTANTIATE_CLASS(DeepHandModelJoint2BoneLayer);
    REGISTER_LAYER_CLASS(DeepHandModelJoint2Bone);

}  // namespace caffe
