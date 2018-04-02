#include <vector>

#include "caffe/layer.hpp"
#include "caffe/util/io.hpp"
#include "caffe/util/math_functions.hpp"
#include "caffe/deep_hand_model_layers.hpp"


namespace caffe {

    template <typename Dtype>
    void DeepHandModelGenRandIndexLayer<Dtype>::LayerSetUp(
        const vector<Blob<Dtype>*>& bottom, const vector<Blob<Dtype>*>& top) {
   
        index_lower_bound_ = this->layer_param_.gen_rand_index_param().index_lower_bound();
        index_upper_bound_ = this->layer_param_.gen_rand_index_param().index_upper_bound();
        batch_size_ = this->layer_param_.gen_rand_index_param().batch_size();
        missing_index_file_ = this->layer_param_.gen_rand_index_param().missing_index_file();
    }
    template <typename Dtype>
    void DeepHandModelGenRandIndexLayer<Dtype>::Reshape(
        const vector<Blob<Dtype>*>& bottom, const vector<Blob<Dtype>*>& top) {
        vector<int> top_shape;
        top_shape.push_back(batch_size_);
        top_shape.push_back(1); //index
        top[0]->Reshape(top_shape);
    }

    template <typename Dtype>
    void DeepHandModelGenRandIndexLayer<Dtype>::Forward_cpu(const vector<Blob<Dtype>*>& bottom,
        const vector<Blob<Dtype>*>& top) {
        
        if (strcmp(missing_index_file_.c_str(), "D:\\") != 0) //!="D:\\"
        {
            FILE *fin_missing_index = fopen(missing_index_file_.c_str(), "r");
            //read number of missing
            fscanf(fin_missing_index, "%d", &num_of_missing_);
            for (int i = 0; i < num_of_missing_; i++)
            {
                fscanf(fin_missing_index, "%d", &missing_index_[i]);
            }
            fclose(fin_missing_index);
        }

        int batSize = batch_size_;      
        Dtype* index_data = top[0]->mutable_cpu_data(); //index      
        srand(time(0));
        for (int t = 0; t < batSize; t++) 
        {
            int rand_index = (rand() * rand() + rand()) % (index_upper_bound_ - index_lower_bound_ + 1) + index_lower_bound_;
            if (strcmp(missing_index_file_.c_str(), "D:\\") != 0) //!="D:\\"
            {
                bool invalid = true;
                while (invalid)
                {
                    bool t_mark = false;
                    for (int i = 0; i < num_of_missing_; i++) if (rand_index == missing_index_[i]) { t_mark = true; break; }
                    //if found in missing array set mark to true so that invalid will be set to true
                    invalid = t_mark;
                    if (invalid) rand_index = (rand() * rand() + rand()) % (index_upper_bound_ - index_lower_bound_ + 1) + index_lower_bound_;
                }                
            }
            index_data[t] = rand_index;            
        }
    }

    template <typename Dtype>
    void DeepHandModelGenRandIndexLayer<Dtype>::Backward_cpu(const vector<Blob<Dtype>*>& top,
        const vector<bool>& propagate_down, const vector<Blob<Dtype>*>& bottom) {
        
    }

#ifdef CPU_ONLY
    STUB_GPU(DeepHandModelGenRandIndexLayer);
#endif

    INSTANTIATE_CLASS(DeepHandModelGenRandIndexLayer);
    REGISTER_LAYER_CLASS(DeepHandModelGenRandIndex);
}
