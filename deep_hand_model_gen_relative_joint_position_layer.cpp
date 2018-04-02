#include <vector>

#include "caffe/layer.hpp"
#include "caffe/util/io.hpp"
#include "caffe/util/math_functions.hpp"
#include "caffe/deep_hand_model_layers.hpp"

namespace caffe {

    template <typename Dtype>
    void DeepHandModelGenRelativeJointPositionLayer<Dtype>::LayerSetUp(
        const vector<Blob<Dtype>*>& bottom, const vector<Blob<Dtype>*>& top) {

        for (int i = 0; i < BoneNum; i++) which_bone[bones[i][0]][bones[i][1]] = i;
        //set zero to f array
        for (int i = 0; i < JointNum; i++)
        {
            for (int j = 0; j < JointNum; j++)
            {
                for (int k = 0; k < BoneNum; k++)
                {
                    f[i][j][k] = 0;
                }
            }
        }

        //for each pair of joint (i,j)
        for (int i = 0; i < JointNum - 1; i++) 
        {
            for (int j = i + 1; j < JointNum; j++) 
            {
                int lca = -1, max_height = -1;
                for (int k = 0; k < JointNum; k++) 
                {
                    int a = i, parent_a = -1;
                    while (a != -1) 
                    {
                        if (a == k) 
                        {
                            parent_a = k;
                            break;
                        }
                        a = parent[a];
                    }
                    int b = j, parent_b = -1;
                    while (b != -1) 
                    {
                        if (b == k) 
                        {
                            parent_b = k;
                            break;
                        }
                        b = parent[b];
                    }
                    if (parent_a == k && parent_b == k) 
                    {
                        if (level[k] > max_height) 
                        {
                            max_height = level[k];
                            lca = k;
                        }
                    }
                }

                int a = i;

                while (a != lca) 
                {                   
                    f[i][j][which_bone[a][parent[a]]] = 1; //sign = +
                    a = parent[a];
                }
                int b = j;
                while (b != lca) 
                {                   
                    f[i][j][which_bone[b][parent[b]]] = -1;
                    b = parent[b];
                }            
            }
        }
    }


    template <typename Dtype>
    void DeepHandModelGenRelativeJointPositionLayer<Dtype>::Reshape(
        const vector<Blob<Dtype>*>& bottom, const vector<Blob<Dtype>*>& top) {
        const int axis = bottom[0]->CanonicalAxisIndex(
            this->layer_param_.inner_product_param().axis());
        vector<int> top_shape = bottom[0]->shape();
        top_shape.resize(axis + 1);
        top_shape[axis] = PairNum * 3;
        top[0]->Reshape(top_shape);
    }

    template <typename Dtype>
    void DeepHandModelGenRelativeJointPositionLayer<Dtype>::Forward_cpu(const vector<Blob<Dtype>*>& bottom,
        const vector<Blob<Dtype>*>& top) {
        int batSize = (bottom[0]->shape())[0];
        const Dtype* bottom_data = bottom[0]->cpu_data();
        Dtype* top_data = top[0]->mutable_cpu_data();
        for (int t = 0; t < batSize; t++) {
            int Tid = t * PairNum * 3;
            for (int p = 0; p < PairNum * 3; p++) top_data[Tid + p] = 0; //clear first
            int t_p = 0;
            for (int i = 0; i < JointNum - 1; i++)
            {
                for (int j = i + 1; j < JointNum; j++)  //for each pair(relative joint difference)
                {
                    int Bid = t * BoneNum * 3;                
                    for (int k = 0; k < BoneNum; k++)
                    {
                        for (int l = 0; l < 3; l++)
                        {
                            top_data[Tid + t_p * 3 + l] += f[i][j][k] * bottom_data[Bid + k * 3 + l];
                            //f[u][v][k]*bone[k];
                        }
                    }
                    t_p++;
                }
            }

        }
    }


    template <typename Dtype>
    void DeepHandModelGenRelativeJointPositionLayer<Dtype>::Backward_cpu(const vector<Blob<Dtype>*>& top,
        const vector<bool>& propagate_down, const vector<Blob<Dtype>*>& bottom) {
        int batSize = (bottom[0]->shape())[0];
        const Dtype* bottom_data = bottom[0]->cpu_data();
        const Dtype* top_diff = top[0]->cpu_diff();
        Dtype* bottom_diff = bottom[0]->mutable_cpu_diff();
        if (propagate_down[0]) {
            for (int t = 0; t < batSize; t++) {
                int Bid = t * BoneNum * 3;
                for (int k = 0; k < BoneNum * 3; k++) bottom_diff[Bid + k] = 0.0;
                for (int k = 0; k < BoneNum; k++) 
                {
                    int p = 0;
                    for (int i = 0; i < JointNum - 1; i++)
                    {
                        for (int j = i + 1; j < JointNum; j++)
                        {
                            int Tid = t * PairNum * 3;
                            for (int l = 0; l < 3; l++)
                            {
                                bottom_diff[Bid + k * 3 + l] += top_diff[Tid + p * 3 + l] * f[i][j][k];
                            }
                            p++;
                        }
                    }
                }
            }
        }
    }

#ifdef CPU_ONLY
    STUB_GPU(DeepHandModelGenRelativeJointPositionLayer);
#endif

    INSTANTIATE_CLASS(DeepHandModelGenRelativeJointPositionLayer);
    REGISTER_LAYER_CLASS(DeepHandModelGenRelativeJointPosition);

}  // namespace caffe
