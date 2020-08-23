#coding: UTF-8
import matplotlib.pyplot as plt #约定俗成的写法plt
import numpy as np
glo_car_width = 1.0
glo_car_length = 1.5


def PolyCoefficients(p, coef_):
    """ Returns a polynomial for ``x`` values for the ``coeffs`` provided.

    The coefficients must be in ascending order (``x**0`` to ``x**o``).
    """
    y= ((((coef_[5] * p + coef_[4]) * p + coef_[3]) * p + coef_[2]) * p +\
              coef_[1]) *\
                 p +\
             coef_[0];
    return y

def basic_map():
    '''build basic map'''
    # plt.axis([0,20,-3,3])
    plt.grid() # 添加网格
    plt.title("dynamic path planning")
    plt.xlabel("station")
    plt.ylabel("lateral")
    x = np.linspace(3,18,6)
    y = np.linspace(-1.8,1.8,7)
    for i in y:
        t = np.ones(6) * i
        plt.plot(x,t,'bo')

def obj_plot(obj_lists):
    '''plot object list'''
    for obj_list in obj_lists:
        car_center_x = obj_list[0] 
        car_center_y = obj_list[1] 

        car_corners_x=[0,0,0,0,0]
        car_corners_y=[0,0,0,0,0]
        car_corners_x[0] = car_center_x - glo_car_width/2 
        car_corners_x[1] = car_center_x + glo_car_width/2 
        car_corners_x[2] = car_center_x + glo_car_width/2 
        car_corners_x[3] = car_center_x - glo_car_width/2 
        car_corners_y[0] = car_center_y + glo_car_length/2 
        car_corners_y[1] = car_center_y + glo_car_length/2 
        car_corners_y[2] = car_center_y - glo_car_length/2 
        car_corners_y[3] = car_center_y - glo_car_length/2
        car_corners_x[4] = car_corners_x[0]
        car_corners_y[4] = car_corners_y[0]

        #plot obj
        plt.plot(car_corners_x,car_corners_y,"k-")
        print(car_corners_x)
        print(car_corners_y)
        



   

def path_plot(Node_lists):
    Node_pre_x = Node_lists[0][0];
    Node_pre_y = Node_lists[0][1];
    for i in range(1,len(Node_lists)):
        Node_cur_x = Node_lists[i][0]
        Node_cur_y = Node_lists[i][1]
        plt.plot([Node_pre_x,Node_cur_x],[Node_pre_y,Node_cur_y],"ro-")
        plt.pause(2)
        Node_pre_x = Node_lists[i][0];
        Node_pre_y = Node_lists[i][1];

    # Y = [0,1.8,0,0,-1.8,0,0]
    # x_ = [0,0]
    # y_ = [0,0]
    # for i in range(1,8):
    #     x_[0] = X[i-1]
    #     x_[1] = X[i]
    #     y_[0] = Y[i-1]
    #     y_[1] = Y[i]
    #     plt.plot(x_,y_,'ro-')
    #     plt.pause(2)

if __name__== '__main__':
    "main function"
    obj = [[6,0],[9,-1.2]]
    path = [[3,0],[6,1.8],[9,0],[12,0],[15,-1.8],[18,0]]
    basic_map()
    obj_plot(obj)
    # path_plot(path)
    x = np.linspace(0, 3, 20)
    # coeffs = [0,0, 0, 0.55555, -0.277778, 0.03]
    coeffs = [0,0,0,0.555556,-0.277778,0.037037]
    plt.plot(x, PolyCoefficients(x, coeffs))
    plt.show()



   



