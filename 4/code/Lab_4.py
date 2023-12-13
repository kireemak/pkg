import matplotlib.pyplot as plt
from tkinter import *
from tkinter import ttk
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import re


class Point():
    def __init__(self, x, y, r=5):
        self.x = x
        self.y = y
        self.r = r


class Program:
    def __init__(self):
        self.p1 = Point(200, 10)
        self.p2 = Point(60, 230)

        self.root = Tk()
        w, h = self.root.winfo_screenwidth(), self.root.winfo_screenheight()
        self.root.geometry(f"900x900+{w//3 - 200}+{h// - 200}")

        self.fig = plt.figure(figsize=(10, 10))

        self.frame1 = Frame(self.root)
        self.frame1.place(x=0, y=0, width=900, height=900)

        self.canvas = FigureCanvasTkAgg(self.fig, self.frame1)
        self.canvas.get_tk_widget().place(x=0, y=0, width=900, height=900)

        self.ax1 = self.fig.add_subplot(3, 3, 1)
        self.ax1.grid()
        self.ax1.minorticks_on()
        self.ax1.grid(which='major', color='k', linewidth=0.1)
        self.ax1.grid(which='minor', color='k', linewidth=0.1)
        self.ax2 = self.fig.add_subplot(3, 3, 3)
        self.ax2.grid()
        self.ax2.minorticks_on()
        self.ax2.grid(which='major', color='k', linewidth=0.1)
        self.ax2.grid(which='minor', color='k', linewidth=0.1)
        self.ax3 = self.fig.add_subplot(3, 3, 7)
        self.ax3.grid()
        self.ax3.minorticks_on()
        self.ax3.grid(which='major', color='k', linewidth=0.1)
        self.ax3.grid(which='minor', color='k', linewidth=0.1)
        self.ax4 = self.fig.add_subplot(3, 3, 9)
        self.ax4.grid()
        self.ax4.minorticks_on()
        self.ax4.grid(which='major', color='k', linewidth=0.1)
        self.ax4.grid(which='minor', color='k', linewidth=0.1)

        self.ax1.set_ylabel("y", labelpad=1, loc='top')
        self.ax1.set_xlabel("x", labelpad=1, loc='right')

        self.ax2.set_ylabel("y", labelpad=1, loc='top')
        self.ax2.set_xlabel("x", labelpad=1, loc='right')

        self.ax3.set_ylabel("y", labelpad=1, loc='top')
        self.ax3.set_xlabel("x", labelpad=1, loc='right')

        self.ax4.set_ylabel("y", labelpad=1, loc='top')
        self.ax4.set_xlabel("x", labelpad=1, loc='right')

        self.frame2 = Frame(self.root)
        self.frame2.place(x=350, y=350, width=200, height=190)

        check = (self.root.register(self.is_valid), "%P")
        self.entr1 = ttk.Entry(self.frame2, validate='key', validatecommand=check)
        self.entr1.place(x=30, y=80, width=60, height=20)
        self.entr2 = ttk.Entry(self.frame2)
        self.entr2.place(x=130, y=80, width=60, height=20)
        self.entr3 = ttk.Entry(self.frame2)
        self.entr3.place(x=30, y=120, width=60, height=20)
        self.entr4 = ttk.Entry(self.frame2)
        self.entr4.place(x=130, y=120, width=60, height=20)
        self.entr5 = ttk.Entry(self.frame2)
        self.entr5.place(x=85, y=160, width=60, height=20)

        self.lbl1 = ttk.Label(self.frame2, text='X1: ')
        self.lbl1.place(x=0, y=80, width=30, height=20)
        self.lbl2 = ttk.Label(self.frame2, text='Y1: ')
        self.lbl2.place(x=100, y=80, width=30, height=20)
        self.lbl3 = ttk.Label(self.frame2, text='X2: ')
        self.lbl3.place(x=0, y=120, width=30, height=20)
        self.lbl4 = ttk.Label(self.frame2, text='Y2: ')
        self.lbl4.place(x=100, y=120, width=30, height=20)
        self.lbl5 = ttk.Label(self.frame2, text='R: ')
        self.lbl5.place(x=55, y=160, width=30, height=20)

        self.btplot1 = Button(self.frame2, text='Process', command=self.draw)
        self.btplot1.place(x=10, y=10, width=180, height=50)

        self.root.mainloop()
    
    def draw(self):
        self.p1.x = int(self.entr1.get()) if self.entr1.get() != '' else 200
        self.p1.y = int(self.entr2.get()) if self.entr1.get() != '' else 10
        self.p2.x = int(self.entr3.get()) if self.entr1.get() != '' else 60
        self.p2.y = int(self.entr4.get()) if self.entr1.get() != '' else 230
        self.p2.r = int(self.entr5.get()) if self.entr1.get() != '' else 2

        step_x, step_y = self.func_step_algorithm(self.p1, self.p2)
        dda_x, dda_y = self.func_DDA_algorithm(self.p1, self.p2)
        b1_x, b1_y = self.func_bresenham_line(self.p1, self.p2)
        b2_x, b2_y = self.func_bresenham_circle(self.p1, self.p2.r)

        self.ax1.clear()
        self.ax1.grid()
        self.ax1.minorticks_on()
        self.ax1.grid(which='major', color='k', linewidth=0.1)
        self.ax1.grid(which='minor', color='k', linewidth=0.1)
        self.ax1.plot(step_y, step_x, '-')
        self.ax1.plot(step_y, step_x, '.')
        self.ax1.title.set_text("Step-by-step")

        self.ax2.clear()
        self.ax2.grid()
        self.ax2.minorticks_on()
        self.ax2.grid(which='major', color='k', linewidth=0.1)
        self.ax2.grid(which='minor', color='k', linewidth=0.1)
        self.ax2.plot(dda_x, dda_y, '-')
        self.ax2.plot(dda_x, dda_y, '.')
        self.ax2.title.set_text("DDA")

        self.ax3.clear()
        self.ax3.grid()
        self.ax3.minorticks_on()
        self.ax3.grid(which='major', color='k', linewidth=0.1)
        self.ax3.grid(which='minor', color='k', linewidth=0.1)
        self.ax3.plot(b1_x, b1_y, '-')
        self.ax3.plot(b1_x, b1_y, '.')
        self.ax3.title.set_text("Bresenham (line)")

        self.ax4.clear()
        self.ax4.grid()
        self.ax4.minorticks_on()
        self.ax4.grid(which='major', color='k', linewidth=0.1)
        self.ax4.grid(which='minor', color='k', linewidth=0.1)
        self.ax4.plot(b2_x, b2_y, 'bo')
        self.ax4.title.set_text("Bresenham (circle)")

        self.ax1.set_ylabel("y", labelpad=1, loc='top')
        self.ax1.set_xlabel("x", labelpad=1, loc='right')
        self.ax2.set_ylabel("y", labelpad=1, loc='top')
        self.ax2.set_xlabel("x", labelpad=1, loc='right')
        self.ax3.set_ylabel("y", labelpad=1, loc='top')
        self.ax3.set_xlabel("x", labelpad=1, loc='right')
        self.ax4.set_ylabel("y", labelpad=1, loc='top')
        self.ax4.set_xlabel("x", labelpad=1, loc='right')

        self.canvas.draw()

    def func_bresenham_circle(self, p1, r):
        x1, y1 = p1.x, p1.y
        x = r
        y = 0
        rerr = 1 - x
        xa, ya = [], []
        while x >= y:
            xa.extend([x + x1, y + x1, -x + x1, -y + x1, -
                       x + x1, -y + x1, x + x1, y + x1])
            ya.extend([y + y1, x + y1, y + y1, x + y1, -
                       y + y1, -x + y1, -y + y1, -x + y1])
            y += 1
            if rerr < 0:
                rerr += 2 * y + 1
            else:
                x -= 1
                rerr += 2 * (y - x + 1)
        return xa, ya

    def func_DDA_algorithm(self, p1, p2):
        x1, y1 = p1.x, p1.y
        x2, y2 = p2.x, p2.y
        dx = abs(x2 - x1)
        dy = abs(y2 - y1)
        L = max(dx, dy)
        x_incr = dx / L
        y_incr = dy / L
        x = x1
        y = y1
        xa, ya = [], []
        for _ in range(L):
            xa.append(x)
            ya.append(y)
            x += x_incr
            y += y_incr
        return xa, ya
    
    def func_step_algorithm(self, p1, p2):
        x1, y1 = p1.x, p1.y
        x2, y2 = p2.x, p2.y
        if x1 > x2:
            x1, x2 = x2, x1
            y1, y2 = y2, y1
        dx = x2 - x1
        dy = y2 - y1
        xa, ya = [], []
        for i in range(x1, x2 + 1):
            xa.append(i)
            ya.append(y1 + dy * (i - x1) / dx)
        return xa, ya

    def func_bresenham_line(self, p1, p2):
        x1, y1 = p1.x, p1.y
        x2, y2 = p2.x, p2.y
        dx = abs(x2 - x1)
        dy = abs(y2 - y1)
        sign_x = 1 if x1 < x2 else -1
        sign_y = 1 if y1 < y2 else -1
        err = dx - dy
        xa, ya = [], []
        while x1 != x2 or y1 != y2:
            xa.append(abs(x1))
            ya.append(abs(y1))
            err2 = err * 2
            if (err2 > -dy):
                err -= dy
                x1 += sign_x
            if (err2 < dx):
                err += dx
                y1 += sign_y
        return xa, ya

    def is_valid(self, newval):
        return re.match("\d+", newval) is not None

if __name__ == "__main__":
    program = Program()