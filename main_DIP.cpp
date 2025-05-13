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

// 自適應中值濾波函式
void adaptiveMedianFilter(int input[][MaxBMPSizeY], int output[][MaxBMPSizeY], int width, int height)
{
    // 遮罩大小從 3x3 開始，最大到 11x11
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            int maskSize = 3;
            while (maskSize <= 11) {
                const int maskLength = maskSize * maskSize;
                int maskValues[maskLength];
                int index = 0;

                // 收集遮罩範圍內的像素值
                for (int y = -maskSize / 2; y <= maskSize / 2; y++) {
                    for (int x = -maskSize / 2; x <= maskSize / 2; x++) {
                        if (i + x >= 0 && i + x < width && j + y >= 0 && j + y < height) {
                            maskValues[index] = input[i + x][j + y];
                            index++;
                        }
                    }
                }

                // 對遮罩內的像素值進行排序
                for (int k = 0; k < index - 1; k++) {
                    for (int l = 0; l < index - k - 1; l++) {
                        if (maskValues[l] > maskValues[l + 1]) {
                            int temp = maskValues[l];
                            maskValues[l] = maskValues[l + 1];
                            maskValues[l + 1] = temp;
                        }
                    }
                }

                // 計算中位數
                int median = maskValues[index / 2];

                // 如果中位數不等於最小和最大值，則使用該中位數
                if (median != maskValues[0] && median != maskValues[index - 1]) {
                    output[i][j] = median;
                    break;
                }

                // 否則，增加遮罩大小並繼續處理
                maskSize += 2;
            }
        }
    }
}

int main()
{
    int width, height;
    int i, j;

    // 開啟並讀取全彩bmp圖檔
    open_bmp("lena_pepper_and_salt_noise10%.bmp", R, G, B, width, height);

    // 執行自適應中值濾波處理
    adaptiveMedianFilter(R, r, width, height);
    adaptiveMedianFilter(G, g, width, height);
    adaptiveMedianFilter(B, b, width, height);

    // 儲存處理結果至新的圖檔中
    save_bmp("lenna_adaptiveMedianFilter.bmp", r, g, b);

    printf("Job Finished!\n");

    // 關閉 bmp 影像圖檔
    close_bmp();

    system("pause");
    return 0;
}

