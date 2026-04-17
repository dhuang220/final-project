#include <iostream>
#include <vector>
using namespace std;

// Creating a decision stump that predicts whether a NHL team makes the playoffs based on how many points they have

struct Node {
    int threshold;
    int left; 
    int right; 
};

void train_test(vector<int> x_data, vector<int> y_data, 
    vector<int>& train_x, vector<int>& train_y, 
    vector<int>& test_x, vector<int>& test_y, double test_split);

class decisionStump {
public:
    Node root;

    // predicts whether a given input is less than or greater than the threshold
    // for this specific case, given an NHL team and their points for the season, 
    // this predicts whether they make or miss the playoffs based on the threshold
    int predict(int data_point) {
        if (data_point < root.threshold) {
            return root.left;
        }
        else {
            return root.right;
        }
    }

    // test out how accurate the model's predictions are
    double evaluate(vector<int> data_x, vector<int> data_y) {
        int correct_predictions = 0;

        for (int i = 0; i < data_x.size(); i++) {
            // checks if the model's prediction matches the true case
            if (predict(data_x[i]) == data_y[i]) {
                correct_predictions++;
            }
        }
        double accuracy = (double)correct_predictions / data_x.size();
        return accuracy;
    }

    // finds the threshold that classifies a binary variable with the best accuracy
    void fit(vector<int> data_x, vector<int> data_y) {
        // set every data point as a threshold and find out which gives the highest accuracy
        double bestAcc = 0;
        int bestThreshold = data_x[0];
        for (int i = 0; i < data_x.size(); i++) {
            root.threshold = data_x[i];
            double acc = evaluate(data_x, data_y); 

            if (acc > bestAcc) {
                bestAcc = acc;
                bestThreshold = data_x[i];
            }
        }

        root.threshold = bestThreshold;

        // after finding the optimal threshold, we use it to find to initialize the left and right leaf
        // this is done by finding whether the majority of 1's is the left or right leaf then labeling the leaf accordingly
        int left_total = 0, right_total = 0;
        int left_ones = 0, right_ones = 0;

        for (int i = 0; i < data_x.size(); i++) {
            if (data_x[i] < root.threshold) {
                left_total++;
                if (data_y[i] == 1) {
                    left_ones++;
                }
            }

            else {
                right_total++;
                if (data_y[i] == 1) {
                    right_ones++;
                }
            }
        }

        // majority of the left is zero
        if (left_total / 2 > left_ones) {
            root.left = 0;
        }
        else {
            root.left = 1;
        }

        // majority of the right is zero
        if (right_total / 2 > right_ones) {
            root.right = 0;
        }
        else {
            root.right = 1;
        }
    }
};

// splitting the data into a testing set and a training set
void train_test(vector<int> x_data, vector<int> y_data, 
                vector<int>& train_x, vector<int>& train_y, 
                vector<int>& test_x, vector<int>& test_y, double test_split) {  

        int test_size = (int)(x_data.size() * test_split);
        int train_size = x_data.size() - test_size;

        // create the training data set
        for (int i = 0; i < train_size; i++) {
            train_x.push_back(x_data[i]);
            train_y.push_back(y_data[i]);
        }

        // create the testing data set
        for (int i = train_size; i < x_data.size(); i++) {
            test_x.push_back(x_data[i]);
            test_y.push_back(y_data[i]);
        }
    }