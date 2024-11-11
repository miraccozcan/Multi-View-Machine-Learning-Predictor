#include <iostream>
#include <vector>
#include <cmath>
#include <memory>

// Observer interface
class IView {
public:
    virtual void displayPrediction(double prediction) = 0;
    virtual ~IView() = default;
};

// Concrete Observer: Console View
class ConsoleView : public IView {
public:
    void displayPrediction(double prediction) override {
        std::cout << "Console Prediction: " << prediction << std::endl;
    }
};

// Concrete Observer: Graphical View (simulated with console output)
class GraphicalView : public IView {
public:
    void displayPrediction(double prediction) override {
        std::cout << "Graphical Prediction: " << prediction << std::endl;
    }
};

// Subject class: Model Trainer
class ModelTrainer {
private:
    std::vector<double> weights;
    const double freq = 50.0;
    const int steps = 360;
    const double PI = 3.141592653589793238;
    std::vector<std::shared_ptr<IView>> views;

    double factorial(int n) {
        double result = 1.0;
        for (int i = 1; i <= n; ++i) {
            result *= i;
        }
        return result;
    }

public:
    void attachView(std::shared_ptr<IView> view) {
        views.push_back(view);
    }

    void notifyViews(double prediction) {
        for (const auto& view : views) {
            view->displayPrediction(prediction);
        }
    }

    int train() {
        const double w = 2.0 * PI * freq;
        const double P = 1.0 / freq;
        double time;

        weights.resize(steps);

        bool modelAccurate = false;
        int termCount = 1;  // Start with the first term (sin(x) = x)

        while (!modelAccurate) {
            // Generate the first quarter of the sine wave with the current number of terms
            for (int i = 0; i <= steps / 4; ++i) {
                time = P * (double)i / steps;
                double x = w * time;
                weights[i] = 0.0;

                // Add terms up to the current term count
                for (int n = 0; n < termCount; ++n) {
                    int power = 2 * n + 1;
                    double term = (pow(-1, n) * pow(x, power)) / factorial(power);
                    weights[i] += term;
                }

                #ifdef TEST_BUILD
                std::cout.precision(6);
                std::cout.setf(std::ios::fixed);
                double trueValue = sin(x);
                std::cout << "i: " << i << " time: " << time << " weights: " << weights[i] << " trueValue: " << trueValue << std::endl;
                #endif
            }

            // Mirror the first quarter to generate the rest of the sine wave
            for (int i = steps / 4; i < steps / 2; ++i) {
                weights[i] = weights[steps / 2 - i];
            }
            for (int i = steps / 2; i < steps; ++i) {
                weights[i] = -weights[i - steps / 2];
            }

            if (errorAnalysis() == 0) {
                modelAccurate = true;
            } else {
                ++termCount;  // Increase the number of terms for the next iteration
            }
        }

        return 0;
    }

    int errorAnalysis() {
        double stdDev = 0.0;
        const double TOLERANCE = 0.001;
        int retVal = 0;
        const double w = 2.0 * PI * freq;
        const double P = 1.0 / freq;
        double diffSum = 0.0;

        for (int i = 0; i < steps; ++i) {
            double time = P * (double)i / steps;
            double trueValue = sin(w * time);
            diffSum += (weights[i] - trueValue) * (weights[i] - trueValue);
        }

        stdDev = sqrt(diffSum / (steps - 1));
        if (stdDev > TOLERANCE) {
            std::cout << "stdDev: " << stdDev << std::endl;
            std::cout << "ERROR: The training model is inaccurate!" << std::endl;
            retVal = -1;
        } else {
            std::cout << "The training model is accurate." << std::endl;
        }
        return retVal;
    }

    double predict(const std::vector<double>& data) {
        double prediction = 0.0;
        for (size_t i = 0; i < data.size() && i < weights.size(); ++i) {
            prediction += weights[i] * data[i];
        }
        notifyViews(prediction);
        return prediction;
    }
};

int main() {
    std::shared_ptr<ModelTrainer> trainer = std::make_shared<ModelTrainer>();
    std::shared_ptr<ConsoleView> consoleView = std::make_shared<ConsoleView>();
    std::shared_ptr<GraphicalView> graphicalView = std::make_shared<GraphicalView>();

    trainer->attachView(consoleView);
    trainer->attachView(graphicalView);

    int ret = trainer->train();
    if (ret == 0) {
        const int TRIALS = 5;
        std::vector<double> inputData;
        for (int i = 0; i < TRIALS; ++i) {
            const int NUM = 1000;
            for (int j = 0; j < NUM; ++j) {
                inputData.push_back((double)(rand() % 1000) / 1000);
            }
            trainer->predict(inputData);
            inputData.clear();
            std::cout << std::endl;
        }
    }

    return ret;
}
