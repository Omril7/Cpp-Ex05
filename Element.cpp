#include "Element.h"

Element::Element() {
    x = NULL;
    t = NULL;
    x_size = 0;
    t_size = 0;
    rank = 0;
    flag = false;
}
Element::Element(double* x, double* t, int x_size, int t_size) {
    this->x = x;
    this->t = t;
    this->x_size = x_size;
    this->t_size = t_size;
    rank = 0;
    flag = false;
}
void Element::updateRank(int r) {
    rank = r;
}
string Element::toString(){
    stringstream ss;
    string s, buffer;
    for(int i = 0; i < t_size ; i ++) {
        ss << t[i];
        ss >> buffer;
        s.append(buffer);
        if(i < t_size-1) {
            s.append(" ");
        }
    }
    return s;
}
int Element::getRank() {
    return rank;
}
bool Element::getFlag() {
    return flag;
}
void Element::setFlag(bool b) {
    flag = b;
}
double Element::getX(int i) { return x[i]; }
void Element::print_double(double d){
    stringstream ss;
    ss << fixed << setprecision(6) << d;
    string s = ss.str();
    s = s.substr(0, s.find_last_not_of('0') + 1);

    if (s.find('.') == (s.size() - 1)) {
        s = s.substr(0, (s.size() - 1));
    }

    cout << s;
}