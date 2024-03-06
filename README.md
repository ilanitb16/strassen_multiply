# Matrix Multiplication Optimization
 The algorithm uses the Strassen algorithm to reduce the computational time of the code.

Definition of Strassen algorithm
Let A,B be two square matrices over R. The goal of matrix multiplication is to calculate the matrix product ![image](https://github.com/ilanitb16/fast_matrix_multiplication/assets/97344492/660bfb7e-abd8-4b88-bba0-d6540c54069f). The algorithm obtains the result matrix by defining seven new matrices:


![image](https://github.com/ilanitb16/fast_matrix_multiplication/assets/97344492/1fa964b8-6c3f-4805-a176-a26b797b1abc)
![image](https://github.com/ilanitb16/fast_matrix_multiplication/assets/97344492/08685517-9237-45fa-ae4e-244a9b9951b6)
![image](https://github.com/ilanitb16/fast_matrix_multiplication/assets/97344492/1f2e9d4c-d6fd-497e-a50c-b117cd54872e)
![image](https://github.com/ilanitb16/fast_matrix_multiplication/assets/97344492/d3ed9ace-def7-4dd3-b607-d88f85c413af)
![image](https://github.com/ilanitb16/fast_matrix_multiplication/assets/97344492/7765758d-c93d-4e6b-a15b-b52e5da1b6f8)
![image](https://github.com/ilanitb16/fast_matrix_multiplication/assets/97344492/b2ebf91c-90cc-4dd3-a699-4613a3870b75)
![image](https://github.com/ilanitb16/fast_matrix_multiplication/assets/97344492/d3bc61dd-3141-43ff-8a5e-a66e0fe9211c)

which effectively reduces the computational complexity of the algorithm a since "only" 7 are computed from 8 products.
 Subsequently it is recombined in the result matrix. The new complexity is ![image](https://github.com/ilanitb16/fast_matrix_multiplication/assets/97344492/90c9a7b3-f71f-4e7e-b55c-3f5562b220cc)

![image](https://github.com/ilanitb16/fast_matrix_multiplication/assets/97344492/af3085e3-7caa-4e28-a267-e0f228230385)

The "trick" of the algorithm consists in avoiding the row-by-column product (standard matrix product algorithm) of matrices, reducing the problem until the seven matrices can be obtained using the numerical products.

![image](https://github.com/ilanitb16/fast_matrix_multiplication/assets/97344492/76849c80-bf38-4fa9-8c47-ca2f074158cf)
![image](https://github.com/ilanitb16/fast_matrix_multiplication/assets/97344492/14afe9d1-18ba-400f-a6ba-b208b2fc43ad)
