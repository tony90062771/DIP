#include <iostream>
#include <stdlib.h>
#include "bmp.h"

using namespace std;

int R[MaxBMPSizeX][MaxBMPSizeY];
int G[MaxBMPSizeX][MaxBMPSizeY];
int B[MaxBMPSizeX][MaxBMPSizeY];
int r[MaxBMPSizeX][MaxBMPSizeY];
int g[MaxBMPSizeX][MaxBMPSizeY];
int b[MaxBMPSizeX][MaxBMPSizeY];

// �۾A�������o�i�禡
void adaptiveMedianFilter(int input[][MaxBMPSizeY], int output[][MaxBMPSizeY], int width, int height)
{
    // �B�n�j�p�q 3x3 �}�l�A�̤j�� 11x11
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            int maskSize = 3;
            while (maskSize <= 11) {
                const int maskLength = maskSize * maskSize;
                int maskValues[maskLength];
                int index = 0;

                // �����B�n�d�򤺪�������
                for (int y = -maskSize / 2; y <= maskSize / 2; y++) {
                    for (int x = -maskSize / 2; x <= maskSize / 2; x++) {
                        if (i + x >= 0 && i + x < width && j + y >= 0 && j + y < height) {
                            maskValues[index] = input[i + x][j + y];
                            index++;
                        }
                    }
                }

                // ��B�n���������ȶi��Ƨ�
                for (int k = 0; k < index - 1; k++) {
                    for (int l = 0; l < index - k - 1; l++) {
                        if (maskValues[l] > maskValues[l + 1]) {
                            int temp = maskValues[l];
                            maskValues[l] = maskValues[l + 1];
                            maskValues[l + 1] = temp;
                        }
                    }
                }

                // �p�⤤���
                int median = maskValues[index / 2];

                // �p�G����Ƥ�����̤p�M�̤j�ȡA�h�ϥθӤ����
                if (median != maskValues[0] && median != maskValues[index - 1]) {
                    output[i][j] = median;
                    break;
                }

                // �_�h�A�W�[�B�n�j�p���~��B�z
                maskSize += 2;
            }
        }
    }
}

int main()
{
    int width, height;
    int i, j;

    // �}�Ҩ�Ū�����mbmp����
    open_bmp("lena_pepper_and_salt_noise10%.bmp", R, G, B, width, height);

    // ����۾A�������o�i�B�z
    adaptiveMedianFilter(R, r, width, height);
    adaptiveMedianFilter(G, g, width, height);
    adaptiveMedianFilter(B, b, width, height);

    // �x�s�B�z���G�ܷs�����ɤ�
    save_bmp("lenna_adaptiveMedianFilter.bmp", r, g, b);

    printf("Job Finished!\n");

    // ���� bmp �v������
    close_bmp();

    system("pause");
    return 0;
}

