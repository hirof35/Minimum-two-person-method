#include <stdio.stdio.h>

// データの構造体
typedef struct {
    double x;
    double y;
} DataPoint;

// モデルパラメータ構造体
typedef struct {
    double w; // 傾き (Weight)
    double b; // 切片 (Bias)
} LinearModel;

// 最小二乗法による学習関数
LinearModel train_linear_regression(DataPoint data[], int size) {
    double sum_x = 0, sum_y = 0, sum_xx = 0, sum_xy = 0;

    for (int i = 0; i < size; i++) {
        sum_x += data[i].x;
        sum_y += data[i].y;
        sum_xx += data[i].x * data[i].x;
        sum_xy += data[i].x * data[i].y;
    }

    double mean_x = sum_x / size;
    double mean_y = sum_y / size;

    LinearModel model;
    // 傾き w = Σ((x - mean_x)(y - mean_y)) / Σ((x - mean_x)^2)
    model.w = (sum_xy - size * mean_x * mean_y) / (sum_xx - size * mean_x * mean_x);
    // 切片 b = mean_y - w * mean_x
    model.b = mean_y - model.w * mean_x;

    return model;
}

// 予測関数
double predict(LinearModel model, double x) {
    return model.w * x + model.b;
}

int main() {
    // 訓練データ（例: 部屋の広さ[x] と 価格[y]）
    DataPoint train_data[] = {
        {10.0, 25.0},
        {20.0, 45.0},
        {30.0, 65.0},
        {40.0, 85.0}
    };
    int data_size = sizeof(train_data) / sizeof(train_data[0]);

    // 1. モデルの学習
    LinearModel model = train_linear_regression(train_data, data_size);
    printf("=== 学習完了 ===\n");
    printf("モデルパラメーター: w = %.2f, b = %.2f\n\n", model.w, model.b);

    // 2. コンソールからの予測実行インタフェース
    double input_x;
    printf("=== 予測モード ===\n");
    printf("広さを入力してください (例: 25.0): ");
    
    if (scanf("%lf", &input_x) == 1) {
        double predicted_y = predict(model, input_x);
        printf("予測された価格: %.2f\n", predicted_y);
    } else {
        printf("無効な入力です。\n");
    }

    return 0;
}
