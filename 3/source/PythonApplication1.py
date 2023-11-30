import tkinter as tk
from tkinter import filedialog
from venv import create

import cv2
import numpy as np
import matplotlib.pyplot as plt
from PIL import Image, ImageTk


class ImageProcessor:

    def __init__(self) -> None:
        self.root = tk.Tk()
        self.root.title("Image processor")
        self.image = cv2.imread("source.jpg")
        self.processed_image = None
        self.panel = tk.Label(self.root)
        self.panel.pack(side="bottom", padx=20, pady=10)
        self.default_image = np.zeros((300, 300, 3), dtype=np.uint8)
        self.default_image[:] = (255, 255, 255)
        
        self.open_btn = tk.Button(
            self.root, text="Open New Image", command=self.func_open_new_image
        )
        self.open_btn.pack(side = "left", padx=7, pady=3)

        self.original_btn = tk.Button(
            self.root, text="Original Image", command=self.func_show_original_image
        )
        self.original_btn.pack(side = "left", padx=7, pady=3)
        
        self.original_btn = tk.Button(
            self.root, text="Adaptive Processing", command=self.func_adaptive_processing
        )
        self.original_btn.pack(side = "left", padx=7, pady=3)
        
        self.original_btn = tk.Button(
            self.root, text="Filter", command=self.func_filter
        )
        self.original_btn.pack(side = "left", padx=7, pady=3)
        
        self.original_btn = tk.Button(
            self.root, text="Local Bernsen", command=self.func_local_threshold_bernsen
        )
        self.original_btn.pack(side = "left", padx=7, pady=3)
        
        self.original_btn = tk.Button(
            self.root, text="Local Otsu", command=self.func_local_threshold_otsu
        )
        self.original_btn.pack(side = "left", padx=7, pady=3)


    def func_resize_image(self, image, width=None, height=None):
        h, w = image.shape[:2]

        if width is None and height is None:
            return image

        if width is None:
            aspect_ratio = height / h
            new_width = int(w * aspect_ratio)
            new_size = (new_width, height)
        else:
            aspect_ratio = width / w
            new_height = int(h * aspect_ratio)
            new_size = (width, new_height)

        resized_img = cv2.resize(image, new_size, interpolation=cv2.INTER_AREA)
        return resized_img


    def func_open_new_image(self):
        file_path = filedialog.askopenfilename()

        if file_path is None:
            self.image = None
            self.processed_image = None
            self.func_display_image(self.default_image)
        else:
            self.image = cv2.imread(file_path)
            self.processed_image = np.copy(self.image)
            self.func_display_image(self.processed_image)


    def func_show_original_image(self):
        if self.image is None:
            return
        self.processed_image = np.copy(self.image)
        self.func_display_image(self.processed_image)


    def func_display_image(self, img):
        img = self.func_resize_image(img, width=400, height=400)
        img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
        img = Image.fromarray(img)
        img = ImageTk.PhotoImage(image=img)
        self.panel.config(image=img)
        self.panel.image = img
        

    def func_adaptive_processing(self) -> None:
        if self.image is None:
            print("Error")
            return
        gray_image = cv2.cvtColor(self.image, cv2.COLOR_BGR2GRAY)
        self.processed_image = cv2.adaptiveThreshold(
            gray_image, 255, cv2.ADAPTIVE_THRESH_MEAN_C, cv2.THRESH_BINARY, 11, 12
        )
        self.func_display_image(self.processed_image)
        

    def func_filter(self) -> None:
        if self.image is None:
            return
        buffer_image = np.array([[1, 1, 1, 1, 1],
                                   [1, 1, 1, 1, 1],
                                   [1, 1, 1, 1, 1],
                                   [1, 1, 1, 1, 1],
                                   [1, 1, 1, 1, 1]
            ])
        self.processed_image = cv2.filter2D(self.image, -1, buffer_image)
        self.func_display_image(self.processed_image)


    def func_local_threshold_bernsen(self, window_size=4, contrast_threshold=2) -> None:
        if len(self.image.shape) == 3:
            gray_image = cv2.cvtColor(self.image, cv2.COLOR_BGR2GRAY)
        else:
            gray_image = self.image

        self.processed_image = gray_image.copy()
        
        height, width = gray_image.shape
        #height, width = self.image.shape
        half_window = window_size // 2
    
        for y in range(half_window, height - half_window):
            for x in range(half_window, width - half_window):
                #window = self.image[y - half_window:y + half_window + 1, x - half_window:x + half_window + 1]
                window = gray_image[y - half_window:y + half_window + 1, x - half_window:x + half_window + 1]
                local_mean = np.mean(window)
                min_w = window.min()
                local_contrast = np.max(window) - min_w
                
                # if local_contrast < contrast_threshold:
                #     #self.processed_image[y, x] = 255 if self.image[y, x] > local_mean else 0
                #     self.processed_image[y, x] = 255 if (self.image[y, x] > local_mean).any() else 0

                # else:
                #     #self.processed_image[y, x] = 255 if self.image[y, x] > (local_mean + np.min(window) / 2) else 0
                #     self.processed_image[y, x] = 255 if (self.image[y, x] > (local_mean + window.min() / 2)).any() else 0

                if local_contrast < contrast_threshold:
                    self.processed_image[y, x] = 255 if gray_image[y, x] > local_mean else 0
                else:
                    self.processed_image[y, x] = 255 if gray_image[y, x] > (local_mean + min_w / 2) else 0

        self.func_display_image(self.processed_image)


    def func_local_threshold_otsu(self, window_size=15) -> None:
        if len(self.image.shape) == 3:
            gray_image = cv2.cvtColor(self.image, cv2.COLOR_BGR2GRAY)
        else:
            gray_image = self.image

        self.processed_image = gray_image.copy()

        height, width = gray_image.shape
        half_window = window_size // 2

        # for y in range(half_window, height - half_window):
        #     for x in range(half_window, width - half_window):
        #         window = gray_image[y - half_window:y + half_window + 1, x - half_window:x + half_window + 1]
                    
        #         _, otsu_threshold = cv2.threshold(window, 0, 255, cv2.THRESH_BINARY + cv2.THRESH_OTSU)
                    
        #         self.processed_image[y, x] = 255 if (gray_image[y, x] > otsu_threshold).any() else 0

        _, self.processed_image = cv2.threshold(gray_image, 0, 255, cv2.THRESH_OTSU)

        self.func_display_image(self.processed_image)


    def run(self) -> None:
        self.func_display_image(self.default_image)
        self.root.mainloop()
 


if __name__ == "__main__":
    processor = ImageProcessor()
    processor.run()
