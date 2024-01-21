# Linear Filtering
## Digital Image Processing - week3


### Linear Filtering(선형 필터링)

- kernel이 영상 위를 움직이면서 처리
- kernel에 선형 연산을 하는 함수를 결합하여 필터 역할 수행


### 기능

1. Gaussian Filter
   * 해당 화소와 가까운 화소에는 가중치를 부여
   * smoothing 효과
   * 잡음 제거
2. Sobel Filter
   * 에지 검출
3. Gaussian pyramid
   * 영상에 대한 down sampling과 gaussian filter에 외한 smoothing을 조합하여 점차 작은 해상도의 영상을 반복적으로 생성
   * down sampling: 화소의 홀수 혹은 짝수 칸만 남겨서 작은 영상을 생성하는 것
4. Laplacian pyramid
   * 높은 해상도의 영상과 낮은 해상도의 영상 간의 차이를 영상으로 저장
   * 더 높은 해상도의 영상을 복원할 수 있음
