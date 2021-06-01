from PIL import Image
from matplotlib import image as mat_image, pyplot


def test_image():
    print("Starting image test...")
    print("1. Load and show image with Pillow")
    image = Image.open('../f1.jpg')
    print(image.format)
    print(image.mode)
    print(image.size)
    image.show()

    print("2. Load and display image with Matplotlib - conversion to numpy")
    data = mat_image.imread('../f1.jpg')
    print(data.dtype)
    print(data.shape)
    pyplot.imshow(data)
    pyplot.show()

    print("3. Resize image to specific dimension")
    image.thumbnail((100, 100))
    print(image.size)
