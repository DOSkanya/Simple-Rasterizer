# Simple-Rasterizer
This is a program about rendering a image of a given obj-format model.

It use Eigen Library as arithmatic tool and Opencv to output the image.

The rasterizer has followed the typical graphic rendering pipeline, including vertex transformation before rasterizing and fragment shading after rasterizing.

And it has realized the per-fragment shading as the illumination model, you can also find per-vertex shading module in the light.h headfile. Just a little adjustment, simply computing illumination before perspective projection.
