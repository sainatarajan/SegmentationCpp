#ifndef FPN_H
#define FPN_H
#include"ResNet.h"
#include"FPNDecoder.h"

class FPNImpl : public torch::nn::Module
{
public:
    FPNImpl(int num_classes, std::string encoder_name = "resnet18", std::string pretrained_path = "", int encoder_depth = 5,
            int decoder_pyramid_channel=256, int decoder_segmentation_channels = 128, std::string decoder_merge_policy = "add",
            float decoder_dropout = 0.2, double upsampling = 4);
    torch::Tensor forward(torch::Tensor x);
private:
    ResNet encoder{nullptr};
    FPNDecoder decoder{nullptr};
    SegmentationHead segmentation_head{nullptr};
    int num_classes = 1;
    std::vector<int> BasicChannels = {3, 64, 64, 128, 256, 512};
    std::vector<int> BottleChannels = {3, 64, 256, 512, 1024, 2048};
    std::map<std::string, std::vector<int>> name2layers = getParams();
};TORCH_MODULE(FPN);

#endif // FPN_H
