#pragma once
#include <string>

namespace WEngine
{
  class ImageLoader
  {
  public:
    struct ImageLoaderConfig
    {
      bool FlipY = true;
    };

  private:
    int width;
    int height;
    int nrChannels;
    unsigned char *data;

  public:
    ImageLoader();
    ~ImageLoader();
    int Width() const;
    int Height() const;
    int NRChannels() const;
    unsigned char *Data() const;
    bool LoadImage(const std::string &path, const ImageLoaderConfig &config);
  };
}
