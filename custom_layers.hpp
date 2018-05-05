#ifndef CAFFE_CUSTOM_LAYERS_HPP_
#define CAFFE_CUSTOM_LAYERS_HPP_

#include <string>
#include <utility>


#include "caffe/blob.hpp"
#include "caffe/common.hpp"
#include "caffe/layer.hpp"
#include "caffe/proto/caffe.pb.h"
#include "caffe/layers/loss_layer.hpp"


#include <vector>
#include "basic.h"
namespace caffe{

    template <typename Dtype>
    class DeepHandModelBone2JointLayer : public Layer<Dtype> {
    public:
        explicit DeepHandModelBone2JointLayer(const LayerParameter& param)
            : Layer<Dtype>(param) { }
        virtual void LayerSetUp(const vector<Blob<Dtype>*>& bottom,
            const vector<Blob<Dtype>*>& top);
        virtual void Reshape(const vector<Blob<Dtype>*>& bottom,
            const vector<Blob<Dtype>*>& top);

        virtual inline const char* type() const { return "DeepHandModelBone2Joint"; }
        virtual inline int ExactNumBottomBlobs() const { return 1; } 
        virtual inline int ExactNumTopBlobs() const { return 1; }

    protected:
        virtual void Forward_cpu(const vector<Blob<Dtype>*>& bottom,
            const vector<Blob<Dtype>*>& top);
        virtual void Backward_cpu(const vector<Blob<Dtype>*>& top,
            const vector<bool>& propagate_down, const vector<Blob<Dtype>*>& bottom);

        int which_bone[JointNum][JointNum];
    };
	
	
    template <typename Dtype>
    class DeepHandModelCubiodIntoGlobalV2Layer : public Layer<Dtype> {
    public:
        explicit DeepHandModelCubiodIntoGlobalV2Layer(const LayerParameter& param)
            : Layer<Dtype>(param) { }
        virtual void LayerSetUp(const vector<Blob<Dtype>*>& bottom,
            const vector<Blob<Dtype>*>& top);
        virtual void Reshape(const vector<Blob<Dtype>*>& bottom,
            const vector<Blob<Dtype>*>& top);

        virtual inline const char* type() const { return "DeepHandModelCubiodIntoGlobalV2"; }
        virtual inline int ExactNumBottomBlobs() const { return 7; }
        virtual inline int ExactNumTopBlobs() const { return 1; }

    protected:
        virtual void Forward_cpu(const vector<Blob<Dtype>*>& bottom,
            const vector<Blob<Dtype>*>& top);
        virtual void Backward_cpu(const vector<Blob<Dtype>*>& top,
            const vector<bool>& propagate_down, const vector<Blob<Dtype>*>& bottom);

    };
	
	
    //Gen the vector point to wrist to parent of wrist (which is (0, 0, 0))
    template <typename Dtype>
    class DeepHandModelGenNegWristBlobLayer : public Layer<Dtype> {
    public:
        explicit DeepHandModelGenNegWristBlobLayer(const LayerParameter& param)
            : Layer<Dtype>(param) { }
        virtual void LayerSetUp(const vector<Blob<Dtype>*>& bottom,
            const vector<Blob<Dtype>*>& top);
        virtual void Reshape(const vector<Blob<Dtype>*>& bottom,
            const vector<Blob<Dtype>*>& top);

        virtual inline const char* type() const { return "DeepHandModelGenNegWristBlob"; }
        virtual inline int ExactNumBottomBlobs() const { return 1; }
        virtual inline int ExactNumTopBlobs() const { return 1; }

    protected:
        virtual void Forward_cpu(const vector<Blob<Dtype>*>& bottom,
            const vector<Blob<Dtype>*>& top);
        virtual void Backward_cpu(const vector<Blob<Dtype>*>& top,
            const vector<bool>& propagate_down, const vector<Blob<Dtype>*>& bottom);

    };

	
    //Generate random index
    template <typename Dtype>
    class DeepHandModelGenRandIndexLayer : public Layer<Dtype> {
    public:
        explicit DeepHandModelGenRandIndexLayer(const LayerParameter& param)
            : Layer<Dtype>(param) { }
        virtual void LayerSetUp(const vector<Blob<Dtype>*>& bottom,
            const vector<Blob<Dtype>*>& top);
        virtual void Reshape(const vector<Blob<Dtype>*>& bottom,
            const vector<Blob<Dtype>*>& top);

        virtual inline const char* type() const { return "DeepHandModelGenRandIndex"; }
        virtual inline int ExactNumBottomBlobs() const { return 0; }
        virtual inline int ExactNumTopBlobs() const { return 1; }

    protected:
        virtual void Forward_cpu(const vector<Blob<Dtype>*>& bottom,
            const vector<Blob<Dtype>*>& top);
        virtual void Backward_cpu(const vector<Blob<Dtype>*>& top,
            const vector<bool>& propagate_down, const vector<Blob<Dtype>*>& bottom);
        int index_lower_bound_;
        int index_upper_bound_;
        int batch_size_;
        string missing_index_file_;
        int missing_index_[11111];
        int num_of_missing_;
    };
	
	
	//For each pair of joints, generate relative joint location difference from the bone vectors
    template <typename Dtype>
    class DeepHandModelGenRelativeJointPositionLayer : public Layer<Dtype> {
    public:
        explicit DeepHandModelGenRelativeJointPositionLayer(const LayerParameter& param)
            : Layer<Dtype>(param) { }
        virtual void LayerSetUp(const vector<Blob<Dtype>*>& bottom,
            const vector<Blob<Dtype>*>& top);
        virtual void Reshape(const vector<Blob<Dtype>*>& bottom,
            const vector<Blob<Dtype>*>& top);

        virtual inline const char* type() const { return "DeepHandModelGenRelativeJointPosition"; }
        virtual inline int ExactNumBottomBlobs() const { return 1; } 
        virtual inline int ExactNumTopBlobs() const { return 1; }

    protected:
        virtual void Forward_cpu(const vector<Blob<Dtype>*>& bottom,
            const vector<Blob<Dtype>*>& top);
        virtual void Backward_cpu(const vector<Blob<Dtype>*>& top,
            const vector<bool>& propagate_down, const vector<Blob<Dtype>*>& bottom);
        int which_bone[JointNum][JointNum];
        int f[JointNum][JointNum][BoneNum];
        //f[i][j][k] means whether the k-th bone is in the term of relative joint location difference of i-th joint and j-th joint
    };
	
	
    //Generate JointNum * 3 - D vector (duplicating wrist)
    template <typename Dtype>
    class DeepHandModelGenWristJointBlobLayer : public Layer<Dtype> {
    public:
        explicit DeepHandModelGenWristJointBlobLayer(const LayerParameter& param)
            : Layer<Dtype>(param) { }
        virtual void LayerSetUp(const vector<Blob<Dtype>*>& bottom,
            const vector<Blob<Dtype>*>& top);
        virtual void Reshape(const vector<Blob<Dtype>*>& bottom,
            const vector<Blob<Dtype>*>& top);

        virtual inline const char* type() const { return "DeepHandModelGenWristJointBlob"; }
        virtual inline int ExactNumBottomBlobs() const { return 1; }
        virtual inline int ExactNumTopBlobs() const { return 1; }

    protected:
        virtual void Forward_cpu(const vector<Blob<Dtype>*>& bottom,
            const vector<Blob<Dtype>*>& top);
        virtual void Backward_cpu(const vector<Blob<Dtype>*>& top,
            const vector<bool>& propagate_down, const vector<Blob<Dtype>*>& bottom);
    };

	

    //The transformation from joint vector to bone vector
    template <typename Dtype>
    class DeepHandModelJoint2BoneLayer : public Layer<Dtype> {
    public:
        explicit DeepHandModelJoint2BoneLayer(const LayerParameter& param)
            : Layer<Dtype>(param) { }
        virtual void LayerSetUp(const vector<Blob<Dtype>*>& bottom,
            const vector<Blob<Dtype>*>& top);
        virtual void Reshape(const vector<Blob<Dtype>*>& bottom,
            const vector<Blob<Dtype>*>& top);

        virtual inline const char* type() const { return "DeepHandModelJoint2Bone"; }
        virtual inline int ExactNumBottomBlobs() const { return 1; }  
        virtual inline int ExactNumTopBlobs() const { return 1; }

    protected:
        virtual void Forward_cpu(const vector<Blob<Dtype>*>& bottom,
            const vector<Blob<Dtype>*>& top);
        virtual void Backward_cpu(const vector<Blob<Dtype>*>& top,
            const vector<bool>& propagate_down, const vector<Blob<Dtype>*>& bottom);

    };
	
	
    //Pinhole Camera in normalized region
    template <typename Dtype>
    class DeepHandModelPinholeCameraLayer : public Layer<Dtype> {
    public:
        explicit DeepHandModelPinholeCameraLayer(const LayerParameter& param)
            : Layer<Dtype>(param) { }
        virtual void LayerSetUp(const vector<Blob<Dtype>*>& bottom,
            const vector<Blob<Dtype>*>& top);

        virtual void Reshape(const vector<Blob<Dtype>*>& bottom,
            const vector<Blob<Dtype>*>& top);

        virtual inline const char* type() const { return "DeepHandModelPinholeCamera"; }
        virtual inline int ExactNumBottomBlobs() const { return 1; }
        virtual inline int ExactNumTopBlobs() const { return 1; }

    protected:
        virtual void Forward_cpu(const vector<Blob<Dtype>*>& bottom,
            const vector<Blob<Dtype>*>& top);
        virtual void Backward_cpu(const vector<Blob<Dtype>*>& top,
            const vector<bool>& propagate_down, const vector<Blob<Dtype>*>& bottom);        
    };
	
	
    template <typename Dtype>
    class DeepHandModelProjectionGlobal2LocalLayer : public Layer<Dtype> {
    public:
        explicit DeepHandModelProjectionGlobal2LocalLayer(const LayerParameter& param)
            : Layer<Dtype>(param) { }
        virtual void LayerSetUp(const vector<Blob<Dtype>*>& bottom,
            const vector<Blob<Dtype>*>& top);
        virtual void Reshape(const vector<Blob<Dtype>*>& bottom,
            const vector<Blob<Dtype>*>& top);

        virtual inline const char* type() const { return "DeepHandModelProjectionGlobal2Local"; }
        virtual inline int ExactNumBottomBlobs() const { return 5; }
        virtual inline int ExactNumTopBlobs() const { return 1; }

    protected:
        virtual void Forward_cpu(const vector<Blob<Dtype>*>& bottom,
            const vector<Blob<Dtype>*>& top);
        virtual void Backward_cpu(const vector<Blob<Dtype>*>& top,
            const vector<bool>& propagate_down, const vector<Blob<Dtype>*>& bottom);

    };
	
	
    //Projection Loss
    template <typename Dtype>
    class DeepHandModelProjectionLossLayer : public LossLayer<Dtype> {
    public:
        explicit DeepHandModelProjectionLossLayer(const LayerParameter& param)
            : LossLayer<Dtype>(param) { }
        virtual void LayerSetUp(const vector<Blob<Dtype>*>& bottom,
            const vector<Blob<Dtype>*>& top);
        virtual void Reshape(const vector<Blob<Dtype>*>& bottom,
            const vector<Blob<Dtype>*>& top);

        virtual inline const char* type() const { return "DeepHandModelProjectionLoss"; }
        virtual inline int ExactNumBottomBlobs() const { return 2; }
        virtual inline int ExactNumTopBlobs() const { return 1; }

    protected:
        virtual void Forward_cpu(const vector<Blob<Dtype>*>& bottom,
            const vector<Blob<Dtype>*>& top);
        virtual void Backward_cpu(const vector<Blob<Dtype>*>& top,
            const vector<bool>& propagate_down, const vector<Blob<Dtype>*>& bottom);
    };

    //read depth image from disk file directly and normalize it no bounding box
    template <typename Dtype>
     class DeepHandModelReadDepthNoBBXWithAVGZLayer : public Layer<Dtype> {
	public:
	    explicit DeepHandModelReadDepthNoBBXWithAVGZLayer(const LayerParameter& param)
			: Layer<Dtype>(param) { }
	    virtual void LayerSetUp(const vector<Blob<Dtype>*>& bottom,
			const vector<Blob<Dtype>*>& top);
	    virtual void Reshape(const vector<Blob<Dtype>*>& bottom,
			const vector<Blob<Dtype>*>& top);

	    virtual inline const char* type() const { return "DeepHandModelReadDepthNoBBXWithAVGZ"; }
	    virtual inline int ExactNumBottomBlobs() const { return 2; }
	    virtual inline int ExactNumTopBlobs() const { return 1; }

	protected:
	    virtual void Forward_cpu(const vector<Blob<Dtype>*>& bottom,
			const vector<Blob<Dtype>*>& top);
	    virtual void Backward_cpu(const vector<Blob<Dtype>*>& top,
			const vector<bool>& propagate_down, const vector<Blob<Dtype>*>& bottom);
	    string file_prefix_;
	    int depth_size_;

    };
	
   //Add vector by constant
    template <typename Dtype>
    class AddVectorByConstantLayer : public Layer<Dtype> {
    public:
        explicit AddVectorByConstantLayer(const LayerParameter& param)
            : Layer<Dtype>(param) { }
        virtual void LayerSetUp(const vector<Blob<Dtype>*>& bottom,
            const vector<Blob<Dtype>*>& top);
        virtual void Reshape(const vector<Blob<Dtype>*>& bottom,
            const vector<Blob<Dtype>*>& top);

        virtual inline const char* type() const { return "AddVectorByConstant"; }
        virtual inline int ExactNumBottomBlobs() const { return 1; }
        virtual inline int ExactNumTopBlobs() const { return 1; }

    protected:
        virtual void Forward_cpu(const vector<Blob<Dtype>*>& bottom,
            const vector<Blob<Dtype>*>& top);
        virtual void Backward_cpu(const vector<Blob<Dtype>*>& top,
            const vector<bool>& propagate_down, const vector<Blob<Dtype>*>& bottom);
        float add_value_;
        int dim_size_;
    };
	
	
    //Cross Validation ten-fold leave one out choose a index from several indexes
    template <typename Dtype>
    class CrossValidationRandomChooseIndexLayer : public Layer<Dtype> {
    public:
        explicit CrossValidationRandomChooseIndexLayer(const LayerParameter& param)
            : Layer<Dtype>(param) { }
        virtual void LayerSetUp(const vector<Blob<Dtype>*>& bottom,
            const vector<Blob<Dtype>*>& top);
        virtual void Reshape(const vector<Blob<Dtype>*>& bottom,
            const vector<Blob<Dtype>*>& top);

        virtual inline const char* type() const { return "CrossValidationRandomChooseIndex"; }
        virtual inline int ExactNumBottomBlobs() const { return 1; }
        virtual inline int ExactNumTopBlobs() const { return 1; }

    protected:
        virtual void Forward_cpu(const vector<Blob<Dtype>*>& bottom,
            const vector<Blob<Dtype>*>& top);
        virtual void Backward_cpu(const vector<Blob<Dtype>*>& top,
            const vector<bool>& propagate_down, const vector<Blob<Dtype>*>& bottom);
        
    };
	
	
    //3D Joint Location Loss
    template <typename Dtype>
    class Joint3DLossLayer : public LossLayer<Dtype> {
    public:
        explicit Joint3DLossLayer(const LayerParameter& param)
            : LossLayer<Dtype>(param) { }
        virtual void LayerSetUp(const vector<Blob<Dtype>*>& bottom,
            const vector<Blob<Dtype>*>& top);
        virtual void Reshape(const vector<Blob<Dtype>*>& bottom,
            const vector<Blob<Dtype>*>& top);

        virtual inline const char* type() const { return "Joint3DLoss"; }
        virtual inline int ExactNumBottomBlobs() const { return 2; }
        virtual inline int ExactNumTopBlobs() const { return 1; }

    protected:
        virtual void Forward_cpu(const vector<Blob<Dtype>*>& bottom,
            const vector<Blob<Dtype>*>& top);
        virtual void Backward_cpu(const vector<Blob<Dtype>*>& top,
            const vector<bool>& propagate_down, const vector<Blob<Dtype>*>& bottom);

    };

	
	
    //square root 3D Joint Location Loss
    template <typename Dtype>
    class Joint3DSquareRootLossLayer : public LossLayer<Dtype> {
    public:
        explicit Joint3DSquareRootLossLayer(const LayerParameter& param)
            : LossLayer<Dtype>(param) { }
        virtual void LayerSetUp(const vector<Blob<Dtype>*>& bottom,
            const vector<Blob<Dtype>*>& top);
        virtual void Reshape(const vector<Blob<Dtype>*>& bottom,
            const vector<Blob<Dtype>*>& top);

        virtual inline const char* type() const { return "Joint3DSquareRootLoss"; }
        virtual inline int ExactNumBottomBlobs() const { return 2; }
        virtual inline int ExactNumTopBlobs() const { return 1; }

    protected:
        virtual void Forward_cpu(const vector<Blob<Dtype>*>& bottom,
            const vector<Blob<Dtype>*>& top);
        virtual void Backward_cpu(const vector<Blob<Dtype>*>& top,
            const vector<bool>& propagate_down, const vector<Blob<Dtype>*>& bottom);

    };
	
	
    //Read blob from disk file just one file
    template <typename Dtype>
    class ReadBlobFromFileLayer : public Layer<Dtype> {
    public:
        explicit ReadBlobFromFileLayer(const LayerParameter& param)
            : Layer<Dtype>(param) { }
        virtual void LayerSetUp(const vector<Blob<Dtype>*>& bottom,
            const vector<Blob<Dtype>*>& top);
        virtual void Reshape(const vector<Blob<Dtype>*>& bottom,
            const vector<Blob<Dtype>*>& top);

        virtual inline const char* type() const { return "ReadBlobFromFile"; }
        virtual inline int ExactNumBottomBlobs() const { return 0; }
        virtual inline int ExactNumTopBlobs() const { return 1; }

    protected:
        virtual void Forward_cpu(const vector<Blob<Dtype>*>& bottom,
            const vector<Blob<Dtype>*>& top);
        virtual void Backward_cpu(const vector<Blob<Dtype>*>& top,
            const vector<bool>& propagate_down, const vector<Blob<Dtype>*>& bottom);
        string file_path_;
        int num_to_read_;
        double t_data[11111];
        int batch_size_;
    };

    //Read blob from disk file indexing
    template <typename Dtype>
    class ReadBlobFromFileIndexingLayer : public Layer<Dtype> {
    public:
        explicit ReadBlobFromFileIndexingLayer(const LayerParameter& param)
            : Layer<Dtype>(param) { }
        virtual void LayerSetUp(const vector<Blob<Dtype>*>& bottom,
            const vector<Blob<Dtype>*>& top);
        virtual void Reshape(const vector<Blob<Dtype>*>& bottom,
            const vector<Blob<Dtype>*>& top);

        virtual inline const char* type() const { return "ReadBlobFromFileIndexing"; }
        virtual inline int ExactNumBottomBlobs() const { return 1; }
        virtual inline int ExactNumTopBlobs() const { return 1; }

    protected:
        virtual void Forward_cpu(const vector<Blob<Dtype>*>& bottom,
            const vector<Blob<Dtype>*>& top);
        virtual void Backward_cpu(const vector<Blob<Dtype>*>& top,
            const vector<bool>& propagate_down, const vector<Blob<Dtype>*>& bottom);
        string file_prefix_;
        int num_to_read_;
        double t_data[11111];
    };
	
	
    //Multiply the vector by a constant number
    template <typename Dtype>
    class ScaleVectorLayer : public Layer<Dtype> {
    public:
        explicit ScaleVectorLayer(const LayerParameter& param)
            : Layer<Dtype>(param) { }
        virtual void LayerSetUp(const vector<Blob<Dtype>*>& bottom,
            const vector<Blob<Dtype>*>& top);
        virtual void Reshape(const vector<Blob<Dtype>*>& bottom,
            const vector<Blob<Dtype>*>& top);

        virtual inline const char* type() const { return "ScaleVector"; }
        virtual inline int ExactNumBottomBlobs() const { return 1; }
        virtual inline int ExactNumTopBlobs() const { return 1; }

    protected:
        virtual void Forward_cpu(const vector<Blob<Dtype>*>& bottom,
            const vector<Blob<Dtype>*>& top);
        virtual void Backward_cpu(const vector<Blob<Dtype>*>& top,
            const vector<bool>& propagate_down, const vector<Blob<Dtype>*>& bottom);
        float scale_factor_;
        int dim_size_;
    };
    
	
	
    //Multiply the [-1, 1] value by standard deviation and add the mean average number
    template <typename Dtype>
    class UnnormalizeLayer : public Layer<Dtype> {
    public:
        explicit UnnormalizeLayer(const LayerParameter& param)
            : Layer<Dtype>(param) { }
        virtual void LayerSetUp(const vector<Blob<Dtype>*>& bottom,
            const vector<Blob<Dtype>*>& top);
        virtual void Reshape(const vector<Blob<Dtype>*>& bottom,
            const vector<Blob<Dtype>*>& top);

        virtual inline const char* type() const { return "Unnormalize"; }
        virtual inline int ExactNumBottomBlobs() const { return 3; }
        virtual inline int ExactNumTopBlobs() const { return 1; }

    protected:
        virtual void Forward_cpu(const vector<Blob<Dtype>*>& bottom,
            const vector<Blob<Dtype>*>& top);
        virtual void Backward_cpu(const vector<Blob<Dtype>*>& top,
            const vector<bool>& propagate_down, const vector<Blob<Dtype>*>& bottom);
    };

	
}

#endif  // CAFFE_COMMON_LAYERS_HPP_

	
	
