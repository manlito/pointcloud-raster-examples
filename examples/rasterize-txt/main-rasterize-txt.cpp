#include <iostream>
#include <pointcloud_raster/raster/pointcloud_rasterizer.hpp>
#include <pointcloud_raster/io/txt/txt_reader.hpp>
#include <filesystem>

int
main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage: ./rasterize_txt input_cloud.txt" << std::endl;
        std::cout << " - input cloud is the path to the file to raster" << std::endl;
        std::cout << " Example: ./pointcloud_raster_app input.txt " << std::endl;
        return EXIT_FAILURE;
    }
    const std::string pointcloudFile(argv[1]);
    const auto pointcloudFilePath = std::filesystem::path(pointcloudFile);
    std::cout << "Rendering pointcloud " << pointcloudFilePath << " to " << pointcloudFilePath.parent_path() << std::endl;

    const std::vector<std::pair<std::string, pointcloud_raster::ViewPointPreset>> viewPresets{
        {"top", pointcloud_raster::ViewPointPreset::TOP}
    };

    pointcloud_raster::raster::PointcloudRasterizer rasterizer;
    for (const auto &[suffix, viewProfile] : viewPresets)
    {
        pointcloud_raster::raster::PointcloudRasterizer::RasterOptions rasterOptions;
        rasterOptions.rasterViewPointPreset = viewProfile;
        rasterOptions.rasterSize = {1024, 1024};
        rasterizer.AddOutputRaster(rasterOptions);
    }
    rasterizer.AddInputProvider(new pointcloud_raster::io::TXTReader(pointcloudFile));
    if (!rasterizer.Rasterize())
    {
        std::cerr << "Rasterization failed" << std::endl;
        return EXIT_FAILURE;
    }

    if (viewPresets.size()!=rasterizer.GetRasterImages().size())
    {
        std::cerr << "Error: Number of resulting rasters is not the same as given input configurations."
                  << "Given " << viewPresets.size() << " vs generated " << rasterizer.GetRasterImages().size()
                  << std::endl;
        return EXIT_FAILURE;
    }

#ifdef POINTCLOUD_RASTER_PNG_SUPPORT
    {
        auto rasterImageIterator = rasterizer.GetRasterImages().begin();
        for (const auto &[suffix, viewProfile] : viewPresets)
        {
            const std::string pngFilePath = pointcloudFilePath.parent_path() / "raster.png";
            std::cout << "Saving image " << pngFilePath << std::endl;
            if (!rasterImageIterator->SaveAsPNG(pngFilePath))
                std::cerr << "Error saving image" << std::endl;
            rasterImageIterator++;
        }
    }
#else
    std::cerr << "Library built without PNG support. No outputs bill be saved." << std::endl;
#endif

    return EXIT_SUCCESS;
}
