#include "engine/util/ImageLoader.h"
#include "engine/util/stb_image.h"
#include <string>
#include <iostream>
#include <cassert>

namespace WEngine
{
  ImageLoader::ImageLoader()
  {
    width = 0;
    height = 0;
    nrChannels = 0;
    data = nullptr;
  }

  ImageLoader::~ImageLoader()
  {
    if (data != nullptr)
    {
      stbi_image_free(data);
    }
  }

  int ImageLoader::Width() const
  {
    return width;
  }
  int ImageLoader::Height() const
  {
    return height;
  }
  int ImageLoader::NRChannels() const
  {
    return nrChannels;
  }
  unsigned char *ImageLoader::Data() const
  {
    return data;
  }
  bool ImageLoader::LoadImage(const std::string &path, const ImageLoaderConfig &config)
  {
    if (data != nullptr)
    {
      stbi_image_free(data);
    }

    stbi_set_flip_vertically_on_load(config.FlipY);
    data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    if (!data)
    {
      std::cout << "Error loading image: " << path << std::endl;
      return false;
    }
    return true;
  }
}
