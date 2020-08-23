def fun(coef_,p):
    y= ((((coef_[5] * p + coef_[4]) * p + coef_[3]) * p + coef_[2]) * p +\
              coef_[1]) *\
                 p +\
             coef_[0];
    return y;

if __name__ == "__main__":
    coef_ =[0,0,0,0.555556,-0.277778,0.037037]
    a=fun(coef_,3)
    print(a)