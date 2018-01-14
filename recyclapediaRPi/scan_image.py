import zbar
import Image

def read_barcode(image_name):
    # create a reader
    scanner = zbar.ImageScanner()

    # configure the reader
    scanner.parse_config('enable')

    # obtain image data
    pil = Image.open(image_name).convert('L')
    width, height = pil.size
    raw = pil.tobytes()

    # wrap image data
    image = zbar.Image(width, height, 'Y800', raw)

    # scan the image for barcodes
    scanner.scan(image)

    # extract results
    ret_val = ''
    for symbol in image:
        # do something useful with results
        print(symbol.data)
        ret_val = symbol.data
        break

    # clean up
    del(image)
    
    # return barcode string
    return ret_val
