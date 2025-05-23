自適應中值濾波(Adaptive Median Filtering) 

自適應中值濾波的基本原理是對圖像中的每個像素應用一個動
態調整的濾波器。該濾波器的大小和形狀取決於像素周圍的鄰域像素
的灰度值。首先，確定一個初始的濾波器大小，然後檢查該濾波器內
的像素灰度值，如果存在異常值（例如噪點），則擴大濾波器的大小，
並再次檢查。重複這個過程，直到找到適當的濾波器大小，然後用該
濾波器對像素進行濾波。 

自適應中值濾波能夠很好地處理各種類型的噪點，包括椒鹽噪
點和高斯噪點。它在保留圖像細節的同時有效地去除噪點，是圖像處
理中常用的一種濾波技術。

