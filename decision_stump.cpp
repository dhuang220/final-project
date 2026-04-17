#include "decision_stump.h"

int main() {
    decisionStump nhl;
    vector<int> train_x;
    vector<int> train_y;
    vector<int> test_x;
    vector<int> test_y;

    // using real data from this year's nhl standings
    vector<int> east_data_x = {92, 113, 99, 78, 95, 91, 87, 98, 106, 77, 92, 84, 100, 109}; // points
    vector<int> east_data_y = { 0,   1,  1,  0,  0,  0,  0,  1,   1,  0,  1,  0,   1,   1}; // 1 if made playoffs, 0 if not

    train_test(east_data_x, east_data_y, train_x, train_y, test_x, test_y, 0.2);
    // test_split is 1/5 of the full data and train_x is 4/5 of the full data

    // fit our data into our decision stump model
    nhl.fit(train_x, train_y);

    // test our fitted model from the training set onto the testing set to get a honest reflection
    // of how our model did on never seen before data
    cout << "threshold: " << nhl.root.threshold << endl;
    cout << "training accuracy: "  << nhl.evaluate(train_x, train_y)*100 << '%' << endl;
    cout << "testing accuracy: "  << nhl.evaluate(test_x, test_y)*100 << '%' << endl;
    
    int points = nhl.root.threshold - 1;
    int prediction = nhl.predict(points);
    if (prediction == 1) {
        cout << points << " points: Made the playoffs" << endl;
    }
    else {
        cout << points << " points: Missed the playoffs" << endl;
    }
    points = nhl.root.threshold + 1;
    prediction = nhl.predict(points);
    if (prediction == 1) {
        cout << points << " points: Made the playoffs" << endl;
    }
    else {
        cout << points << " points: Missed the playoffs" << endl;
    }


    // try with another set of data
    cout << '\n' << "Testing results with new dataset" << '\n' << endl;
    train_x.clear();
    train_y.clear();
    test_x.clear();
    test_y.clear();

    vector<int> west_data_x = {121, 112, 104, 95, 93, 90, 58, 72, 77, 79, 82, 86, 92, 92, 86, 86};
    vector<int> west_data_y = {  1,   1,   1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  1,  1,  0,  0};
    
    train_test(west_data_x, west_data_y, train_x, train_y, test_x, test_y, 0.2);

    nhl.fit(train_x, train_y);

    cout << "threshold: " << nhl.root.threshold << endl;
    cout << "training accuracy: "  << nhl.evaluate(train_x, train_y)*100 << '%' << endl;
    cout << "testing accuracy: "  << nhl.evaluate(test_x, test_y)*100 << '%' << endl;

    points = nhl.root.threshold - 1;
    prediction = nhl.predict(points);
    if (prediction == 1) {
        cout << points << " points: Made the playoffs" << endl;
    }
    else {
        cout << points << " points: Missed the playoffs" << endl;
    }
    points = nhl.root.threshold + 1;
    prediction = nhl.predict(points);
    if (prediction == 1) {
        cout << points << " points: Made the playoffs" << endl;
    }
    else {
        cout << points << " points: Missed the playoffs" << endl;
    }
}