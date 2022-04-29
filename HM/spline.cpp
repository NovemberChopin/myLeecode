 
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <math.h>
#include <Eigen/Dense>
#include<ctime>

using namespace std;
 
class BSpline {
public:
  BSpline(int cpNum, int degree);
  ~BSpline();

  vector<double> GetKnots();
  vector<double> EstimateParams(vector<std::pair<double, double>>& tra);
  void setCP(vector<std::pair<double, double>> cp_point) {
    cp = cp_point;
    for (int i=0; i<int(cp.size()); ++i)
      cout << cp[i].first << " " << cp[i].second << endl;
  }
  vector<double> Coeffs(double uq);
  std::pair<double, double> DeBoor(double x);
  vector<std::pair<double, double>> GetControlPoints(
                                vector<std::pair<double, double>>& tra);
  vector<std::pair<double, double>> GetBSpline();

  bool readCsv(vector<std::pair<double, double>> *tra, string fileDir);
  double strDou(string str);

private:
  int cpNum;
  int degree;
  vector<std::pair<double, double>> cp;
  int m;
  vector<double> knots_;
  vector<double> param_;
};

BSpline::~BSpline() {}

BSpline::BSpline(int cpNum, int degree):cpNum(cpNum), degree(degree) {}

double BSpline::strDou(string str) {	//string 转换 double
	char *ch = new char[0];
	double d;
	for (int i = 0; i != str.length(); i++)
		ch[i] = str[i];
	d = atof(ch);
	return d;
}

bool BSpline::readCsv(vector<std::pair<double, double>> *tra, string fileDir) {
  
  std::ifstream inFile(fileDir, ios::in);
  if (!inFile) {
      cout << "打开文件失败！" << endl;
      exit(1);
  }
  int i = 0;
  string line;
  string field;
  while (getline(inFile, line)) {
    string field;
    istringstream sin(line);

    getline(sin, field, ',');
    // double first stod(field.c_str());
    double first = strDou(field);

    getline(sin, field, ',');
    // double second stod(field.c_str());
    double second = strDou(field);
    tra->emplace_back(std::make_pair(first, second));
  }
  return true;
}

vector<double> BSpline::EstimateParams(vector<std::pair<double, double>>& tra) {
  // method="centripetal"
  double L = 0;
  vector<double> Li;
  for (int i=1; i<int(tra.size()); ++i) {
    double dis = pow(pow(tra[i].first, 2) + pow(tra[i].second, 2), 0.5);
    Li.push_back(dis);
    L += dis;
  }
  vector<double> param(1, 0);
  for (int i=0; i<int(Li.size()); ++i) {
    double Lki = 0;
    for (int j=0; j<i+1; j++)
      Lki += Li[j];
    param.push_back(Lki/L);
  }
  param_ = param;
  return param;
}

vector<double> BSpline::GetKnots() {
  vector<double> knots(degree+1, 0);
  m = cpNum + degree + 1;
  // 中间节点个数
  int knot_num_mid = m+1 - 2*(degree+1);
  // 节点平均步长
  double aver_size = 1.0 / (knot_num_mid+1);
  double k_temp = 0;
  for (int j=1; j<knot_num_mid+1; ++j) {
    k_temp += aver_size;
    knots.push_back(k_temp);
  }
  // 添加 degree+1 个 1
  vector<double> add(degree+1, 1);
  knots.insert(knots.end(), add.begin(), add.end());
  knots_ = knots;
  return knots;
}

vector<double> BSpline::Coeffs(double uq) {
  // N[] holds all intermediate and the final results
  // in fact N is longer than control points,this is just to hold the 
  // intermediate value, at last, we juest extract a part of N,that is N[0:n+1]
  vector<double> N(m+1, 0);
  if (uq == knots_[0]) {
    N[0] = 1.0;
    vector<double> res(N.begin(), N.begin()+cpNum+1);
    return res;
  } else if (uq == knots_[m]) {
    N[cpNum] = 1.0;
    vector<double> res(N.begin(), N.begin()+cpNum+1);
    return res;
  }
  // now u is between u0 and um, first find k uq in span [uk,uk+1)
  int k = 0;
  for (unsigned int i=0; i<knots_.size(); ++i) {
    if (uq < knots_[i]) {
      k = i-1;
      break;
    }
    if (i == knots_.size()-1) 
      k = knots_.size()-1;
  }


  N[k] = 1.0;   // degree 0
  for (int i=1; i<degree+1; ++i) {
    int r_max = m - i - 1;
    if (k - i >= 0) {
      if (knots_[k+1]-knots_[k-i+1] > 0) {
        N[k-i] = (knots_[k+1]-uq) / (knots_[k+1]-knots_[k-i+1])*N[k-i+1];
      } else {
        N[k-i] = (knots_[k+1]-uq) / 1*N[k-i+1];
      }
    }
    for (int j=k-i+1; j<k; ++j) {
      if (j>=0 && j<=r_max) {
        double d1 = knots_[j+i] - knots_[j];
        double d2 = knots_[j+i+1] - knots_[j+1];
        if (d1 == 0) d1 = 1;
        if (d2 == 0) d2 = 1;
        N[j] = (uq-knots_[j])/d1*N[j]+(knots_[j+i+1]-uq)/d2*N[j+1];
      }
    }

    if (k <= r_max) {
      if (knots_[k+i]-knots_[k])
        N[k] = (uq-knots_[k])/(knots_[k+i]-knots_[k])*N[k];
      else 
        N[k] = (uq-knots_[k]) / 1*N[k];
    }
  }
  vector<double> res(N.begin(), N.begin()+cpNum+1);
  return res;
}

std::pair<double, double> BSpline::DeBoor(double uq) {
  int k = 0;
  for (unsigned int i=0; i<knots_.size(); ++i) {
    if (uq < knots_[i]) {
      k = i-1;
      break;
    }
    if (i == knots_.size()-1) 
      k = knots_.size()-1;
  }

  // inserting uq h times
  int sk = 0, h = 0;
  int i=0;
  for (; i<int(knots_.size()); ++i) {
    if (uq == knots_[i]) {
      for (int j=0; j<int(knots_.size()); ++j) {
        if (knots_[j] == knots_[k])
          sk++;
      }
      h = degree - sk;
      break;
    }
  }
  if (i == knots_.size()) {
    sk = 0;
    h = degree;
  }
  // cout << k << " " << sk << " " << h << endl;
  if (h == -1) {
    if (k == degree) return cp.front();  // first
    else if (k == m) return cp.back();  // last
  }

  vector<std::pair<double, double>> P;
  for (i=k-degree; i<k-sk+1; ++i) {
    P.push_back(std::make_pair(cp[i].first, cp[i].second));
  }
  int dis = k - degree;

  for (int r=1; r<h+1; ++r) {
    vector<std::pair<double, double>> temp;
    for (int i=k-degree+r; i<k-sk+1; ++i) {
      double a_ir = (uq-knots_[i]) / (knots_[i+degree-r+1]-knots_[i]);
      double x = (1-a_ir)*P[i-dis-1].first + a_ir*P[i-dis].first;
      double y = (1-a_ir)*P[i-dis-1].second + a_ir*P[i-dis].second;
      temp.push_back(std::make_pair(x, y));
    }
    for (int i=0; i<int(temp.size()); ++i) {
      P[i+k-degree+r-dis] = temp[i];
    }
  }
  return P.back();
}

vector<std::pair<double, double>> BSpline::GetControlPoints(
                                vector<std::pair<double, double>>& tra) {
  int num = tra.size()-1; 
  
  vector<vector<double>> N(param_.size(), vector<double>(cpNum+1));
  
  for (unsigned int i=0; i<param_.size(); ++i) {
    vector<double> N_temp = Coeffs(param_[i]);
    N[i] = N_temp;
  }

  Eigen::MatrixXd Q(tra.size()-2, 2);   // Q 18*2
  for (unsigned int i=1; i<num; ++i) {
    // Eigen::Vector2d Q_temp = tra[i] - N[i][0]*tra[0] - N[i][cpNum]*tra.back();
    double x = tra[i].first - N[i][0]*tra[0].first - N[i][cpNum]*tra.back().first;
    double y = tra[i].second - N[i][0]*tra[0].second - N[i][cpNum]*tra.back().second;
    Q(i-1, 0) = x;
    Q(i-1, 1) = y;
  }
  // cout << "---------------" << endl;
  // cout << Q << endl;
  
  Eigen::MatrixXd b(cpNum-1, 2);  // b 7*2
  for (int i=1; i<cpNum; ++i) {
    Eigen::Vector2d b_temp = Eigen::Vector2d::Zero(2, 1);
    for (unsigned int k=1; k<num; ++k)
      b_temp += N[k][i]*Q.row(k-1);
    // Eigen 赋值操作
    b(i-1, 0) = b_temp[0];
    b(i-1, 1) = b_temp[1];
  }
  // N: 20 * 9     A: 20 * 7
  Eigen::MatrixXd A = Eigen::MatrixXd::Zero(tra.size(), cpNum-1);
  for (unsigned int i=0; i<N.size(); ++i) {
    for (unsigned int j=1; j < N[0].size()-1; ++j) {
      A(i, j-1) = N[i][j];
    }
  }
  Eigen::MatrixXd B = A.transpose() * A;  // B: 7*7
  Eigen::MatrixXd cp_mid = B.lu().solve(b);

  // 控制点首尾值为原数据首尾值
  cp.push_back(std::make_pair(tra.front().first, tra.front().second));
  for (int i=0; i<cp_mid.rows(); ++i) {
    // 把 Eigen 数据赋值给 成员变量 cp
    cp.push_back(std::make_pair(cp_mid.row(i)[0], cp_mid.row(i)[1]));
  }
  cp.push_back(std::make_pair(tra.back().first, tra.back().second));

  return cp;
}

vector<std::pair<double, double>> BSpline::GetBSpline() {
  vector<std::pair<double, double>> spline;
  for (int i=0; i<101; ++i) {
    spline.push_back(DeBoor(0.01*i));
  }
  return spline;
}

int main() {
  // vector<std::pair<double, double>> tra;
  // BSpline bs(8, 3);
  // bs.readCsv(&tra);

  // clock_t start_time, end_time;
  // start_time = clock();
  // vector<double> knots = bs.GetKnots();
  // vector<double> param = bs.EstimateParams(tra);
  // // for (int i=0; i<int(knots.size()); i++) {
  // //   cout << knots[i] << " ";
  // // }
  // // cout << endl;
  // // for (int i=0; i<int(param.size()); i++) {
  // //   cout << param[i] << " ";
  // // }
  // // cout << endl;
  
  // std::ofstream outfile;
  // outfile.open("./cp_point.csv");

  // vector<std::pair<double, double>> cp_points = bs.GetControlPoints(tra);
  // // for (int i=0; i < int(cp_points.size()); ++i) {
  // //   cout << cp_points[i].first << " " << cp_points[i].second << endl;
  // //   outfile << cp_points[i].first << "," << cp_points[i].second << "\n";
  // // }
  // cout << endl;
  // std::vector<std::pair<double, double>> spline = bs.GetBSpline();
  // end_time = clock();
  // cout << "The run time is: " <<(double)(end_time - start_time) / CLOCKS_PER_SEC << "s" << endl;
  // // for (int i=0; i<int(spline.size()); ++i) {
  // //   outfile << spline[i].first << "," << spline[i].second << "\n";
  // // }
  // outfile.close();

  /**
   * 从控制点还原 曲线
   */
  std::ofstream outfile;
  outfile.open("./spline_cpp.csv");
  BSpline bs2(8, 3);
  vector<std::pair<double, double>> cp_points;
  string fileDir = "./cp_point.csv";
  bs2.readCsv(&cp_points, fileDir);
  bs2.GetKnots();
  bs2.setCP(cp_points);
  vector<std::pair<double, double>> curve = bs2.GetBSpline();
  for (int i=0; i < int(curve.size()); ++i) {
    outfile << curve[i].first << "," << curve[i].second << "\n";
  }
  outfile.close();
	return 0;
}