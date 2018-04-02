#include <algorithm>
#include "caffe/layer.hpp"
#include "caffe/deep_hand_model_layers.hpp"
namespace caffe {

    template <typename Dtype>
    void DeepHandModelProjectionGlobal2LocalLayer<Dtype>::LayerSetUp(const vector<Blob<Dtype>*>& bottom,
        const vector<Blob<Dtype>*>& top) {
    }

    template <typename Dtype>
    void DeepHandModelProjectionGlobal2LocalLayer<Dtype>::Reshape(const vector<Blob<Dtype>*>& bottom,
        const vector<Blob<Dtype>*>& top) {
        const int axis = bottom[0]->CanonicalAxisIndex(
            this->layer_param_.inner_product_param().axis());
        vector<int> top_shape = bottom[0]->shape();
        top_shape.resize(axis + 1);
        top_shape[axis] = JointNum * 2;
        top[0]->Reshape(top_shape);
    }

    template <typename Dtype>
    void DeepHandModelProjectionGlobal2LocalLayer<Dtype>::Forward_cpu(const vector<Blob<Dtype>*>& bottom,
        const vector<Blob<Dtype>*>& top) {
        const Dtype* joint_2d_data = bottom[0]->cpu_data();
        const Dtype* u_lb_data = bottom[1]->cpu_data();        
        const Dtype* v_lb_data = bottom[2]->cpu_data();
        const Dtype* u_ub_data = bottom[3]->cpu_data();
        const Dtype* v_ub_data = bottom[4]->cpu_data();
        
        Dtype* top_data = top[0]->mutable_cpu_data();
        const int batSize = (bottom[0]->shape())[0];
        for (int t = 0; t < batSize; t++) {
            double u_lb = u_lb_data[t];
            double v_lb = v_lb_data[t];
            double u_ub = u_ub_data[t];
            double v_ub = v_ub_data[t];
            for (int i = 0; i < JointNum; i++) 
            {
                int Bid = t * JointNum * 2;
                double normalized_u = (joint_2d_data[Bid + i * 2] - u_lb) / (u_ub - u_lb);
                double normalized_v = (joint_2d_data[Bid + i * 2 + 1] - v_lb) / (v_ub - v_lb);
                //NOTE The negative sign
                int Tid = t * JointNum * 2;
                top_data[Tid + i * 2] = normalized_u;
                top_data[Tid + i * 2 + 1] = normalized_v;                
            }

        }
    }


    template <typename Dtype>
    void DeepHandModelProjectionGlobal2LocalLayer<Dtype>::Backward_cpu(const vector<Blob<Dtype>*>& top,
        const vector<bool>& propagate_down,
        const vector<Blob<Dtype>*>& bottom) {

        const Dtype* bottom_data = bottom[0]->cpu_data();
        const Dtype* top_diff = top[0]->cpu_diff();
        Dtype* bottom_diff = bottom[0]->mutable_cpu_diff();

        const int batSize = (bottom[0]->shape())[0];

    }

#ifdef CPU_ONLY
    STUB_GPU(DeepHandModelProjectionGlobal2LocalLayer);
#endif

    INSTANTIATE_CLASS(DeepHandModelProjectionGlobal2LocalLayer);
    REGISTER_LAYER_CLASS(DeepHandModelProjectionGlobal2Local);
}  // namespace caffe
