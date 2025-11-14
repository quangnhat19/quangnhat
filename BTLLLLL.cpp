#include <iostream>
#include <string>
#include <cctype>
#include <windows.h>
#include <sstream>
#include <limits> 
using namespace std;

// ================= HAM NHAP SO NGUYEN AN TOAN =================
int inputIntSafe(const string &prompt, const string &errMsg = "Ban nhap sai! Vui long nhap lai.") {
    string line;
    int value;
    while (true) {
        cout << prompt;
        getline(cin, line);
        if (line.empty()) {
            cout << errMsg << endl;
            continue;
        }
        stringstream ss(line);
        if (ss >> value && ss.eof()) return value;
        cout << errMsg << endl;
    }
}

// ================= HAM MAU =================
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// ================= CLEAR MAN HINH =================
void clearScreen() {
    system("cls");
}

// ================= CAU TRUC DU LIEU =================
struct CauHoi {
    string noiDung, a, b, c, d;
    char dapAnDung;
};

struct HocSinh {
    string tenDN, matKhau, ten, lop;
    float diem = 0;
    string mshs;
};

struct GiaoVien {
    string tenDN, matKhau, ten, mon, lopPhuTrach;
};

struct NodeGV { GiaoVien data; NodeGV* next; };
struct NodeHS { HocSinh data; NodeHS* next; };
struct NodeCH { CauHoi data; NodeCH* next; };

// ================= LOP QUAN LY =================
class QuanLy {
public:
    NodeGV* headGV = NULL;
    NodeHS* headHS = NULL;
    NodeCH* headCH = NULL;
    int thoiGianThi = 5;

    void menuAdmin();
    void themGiaoVien();
    void xoaGiaoVien();
    void xemDSGiaoVien();

    void menuGiaoVien();
    void themHocSinh();
    void xoaHocSinh();
    void datThoiGianThi();
    void taoCauHoi();
    void xemDSHocSinh();

    void menuHocSinh(HocSinh* hs);
    void lamBaiThi(string user);

    bool dangNhapAdmin();
    GiaoVien* dangNhapGV();
    HocSinh* dangNhapHS();
};

// ================= CAC HAM LINKED LIST =================
void themCuoiGV(NodeGV*& head, GiaoVien gv) {
    NodeGV* node = new NodeGV{ gv, NULL };
    if (!head) { head = node; return; }
    NodeGV* temp = head;
    while (temp->next) temp = temp->next;
    temp->next = node;
}

void themCuoiHS(NodeHS*& head, HocSinh hs) {
    NodeHS* node = new NodeHS{ hs, NULL };
    if (!head) { head = node; return; }
    NodeHS* temp = head;
    while (temp->next) temp = temp->next;
    temp->next = node;
}

void themCuoiCH(NodeCH*& head, CauHoi ch) {
    NodeCH* node = new NodeCH{ ch, NULL };
    if (!head) { head = node; return; }
    NodeCH* temp = head;
    while (temp->next) temp = temp->next;
    temp->next = node;
}

bool xoaGV(NodeGV*& head, string user) {
    NodeGV* temp = head, *prev = NULL;
    while (temp) {
        if (temp->data.tenDN == user) {
            if (prev) prev->next = temp->next;
            else head = temp->next;
            delete temp; return true;
        }
        prev = temp; temp = temp->next;
    }
    return false;
}

bool xoaHS(NodeHS*& head, string user) {
    NodeHS* temp = head, *prev = NULL;
    while (temp) {
        if (temp->data.tenDN == user) {
            if (prev) prev->next = temp->next;
            else head = temp->next;
            delete temp; return true;
        }
        prev = temp; temp = temp->next;
    }
    return false;
}

// ================= MENU ADMIN =================
void QuanLy::themGiaoVien() {
    int n;

    cout << "Nhap so luong giao vien: ";
    while (true) {
        cin >> n;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Chi duoc nhap so Vui long nhap lai: ";
            continue;
        }

        if (n <= 0) {
            cout << "So luong phai lon hon 0 Nhap lai: ";
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        break;
    }
    for (int i = 0; i < n; i++) {
        GiaoVien gv;

        cout << "\n=== GIAO VIEN " << i + 1 << " ===\n";

        cout << "Ten dang nhap: ";
        getline(cin, gv.tenDN);

        cout << "Mat khau: ";
        getline(cin, gv.matKhau);

        cout << "Ten giao vien: ";
        getline(cin, gv.ten);

        cout << "Mon day: ";
        getline(cin, gv.mon);

        cout << "Lop phu trach: ";
        getline(cin, gv.lopPhuTrach);

        themCuoiGV(headGV, gv);
    }

    cout << "\nDa them giao vien\n";
}

void QuanLy::xoaGiaoVien() {
    string user;

    cout << "\n===== XOA GIAO VIEN =====\n";
    cout << "Nhap ten dang nhap giao vien can xoa: ";
    getline(cin, user);

    bool ok = xoaGV(headGV, user);

    if (ok) {
        cout << "\n>>> Da xoa giao vien co ten dang nhap: " << user << "\n";
        cout << "\n===== DANH SACH GIAO VIEN SAU KHI XOA =====\n";

        NodeGV* temp = headGV;
        if (!temp) {
            cout << "Danh sach rong!\n";
            return;
        }

        while (temp) {
            cout << "- Ten: " << temp->data.ten
                << " | Mon: " << temp->data.mon
                << " | Lop: " << temp->data.lopPhuTrach
                << " | User: " << temp->data.tenDN << endl;
            temp = temp->next;
        }
    }
    else {
        cout << "\n>>> Khong tim thay giao vien nao co ten dang nhap: " << user << "\n";
    }
}

void QuanLy::xemDSGiaoVien() {
    cout << "\n=== DANH SACH GIAO VIEN ===\n";
    NodeGV* temp = headGV;
    while (temp) {
        cout << "Ten: " << temp->data.ten
             << " | Mon: " << temp->data.mon
             << " | Lop: " << temp->data.lopPhuTrach << endl;
        temp = temp->next;
    }
}

void QuanLy::menuAdmin() {
    clearScreen();
    int lua;

    do {
        setColor(9);
        cout << "\n===== MENU ADMIN =====\n";
        setColor(11);
        cout << "1. Them giao vien\n";
        cout << "2. Xoa giao vien\n";
        cout << "3. Xem danh sach giao vien\n";
        cout << "0. Quay lai\n";
        setColor(7);

        // dong bo an toan: doc dong cuoi tu input truoc khi su dung cin >>
        cin.clear();
        cout << "Chon: ";
        cin >> lua;

        // kiem tra va bat nhap lai neu sai
        while (cin.fail() || lua < 0 || lua > 3) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Lua chon khong hop le! Vui long chon lai (0 - 3): ";
            cin >> lua;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (lua) {
            case 1: themGiaoVien(); break;
            case 2:
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  
    xoaGiaoVien();
    break;

            case 3: xemDSGiaoVien(); break;
        }
    } while (lua != 0);
}


// ================= MENU GIAO VIEN =================
void QuanLy::themHocSinh() {
    int n;

    cout << "Nhap so luong hoc sinh muon them: ";

    // ======== NHAP SO AN TOAN ========
    while (true) {
        cin >> n;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Chi duoc nhap so! Vui long nhap lai: ";
            continue;
        }

        if (n <= 0) {
            cout << "So luong phai lon hon 0! Nhap lai: ";
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        break;
    }

    // ======== NHAP DANH SACH HOC SINH ========
    for (int i = 0; i < n; i++) {
        HocSinh hs;

        cout << "\n=== HOC SINH " << i + 1 << " ===\n";

        cout << "Ma so hoc sinh (MSHS): ";
        getline(cin, hs.mshs);     

        cout << "Ten dang nhap(MSHS) ";
        getline(cin, hs.tenDN);

        cout << "Mat khau: ";
        getline(cin, hs.matKhau);

        cout << "Ten hoc sinh: ";
        getline(cin, hs.ten);

        cout << "Lop: ";
        getline(cin, hs.lop);

        themCuoiHS(headHS, hs);
    }

    cout << "\nDa them hoc sinh\n";
}



void QuanLy::xoaHocSinh() {
    string user;

    cout << "\n===== XOA HOC SINH =====\n";
    cout << "Nhap ten dang nhap hoc sinh can xoa: ";
    getline(cin, user);

    bool ok = xoaHS(headHS, user);

    if (ok) {
        cout << "\n>>> Da xoa hoc sinh co ten dang nhap: " << user << "\n";

        cout << "\n===== DANH SACH HOC SINH SAU KHI XOA =====\n";

        NodeHS* temp = headHS;
        if (!temp) {
            cout << "Danh sach rong\n";
            return;
        }

        while (temp) {
    cout << "- MSSV: " << temp->data.mshs 
         << " | Ten: " << temp->data.ten
         << " | Lop: " << temp->data.lop
         << " | User: " << temp->data.tenDN
         << " | Diem: " << temp->data.diem
         << endl;
    temp = temp->next;
}

    }
    else {
        cout << "\n>>> Khong tim thay hoc sinh co ten dang nhap: " << user << "!\n";
    }
}


void QuanLy::datThoiGianThi() {
    cout << "Nhap thoi gian lam bai (phut): ";
    cin >> thoiGianThi;
    cout << "Da cai dat\n";
}

void QuanLy::taoCauHoi() {
    int n;
    cout << "Nhap so luong cau hoi: ";
    cin >> n;
    cin.ignore();

    for (int i = 0; i < n; i++) {
        CauHoi ch;
        cout << "\nNhap noi dung cau hoi: "; getline(cin, ch.noiDung);
        cout << "A: "; getline(cin, ch.a);
        cout << "B: "; getline(cin, ch.b);
        cout << "C: "; getline(cin, ch.c);
        cout << "D: "; getline(cin, ch.d);
        cout << "Dap an dung (A/B/C/D): ";
cin >> ch.dapAnDung;

while (toupper(ch.dapAnDung) < 'A' || toupper(ch.dapAnDung) > 'D') {
    cout << "Chi duoc nhap A, B, C, hoac D Nhap lai: ";
    cin >> ch.dapAnDung;
}

cin.ignore(numeric_limits<streamsize>::max(), '\n');

        themCuoiCH(headCH, ch);
    }
    cout << "\nDa tao cau hoi\n";
}
void QuanLy::xemDSHocSinh() {
    cout << "\n===== DANH SACH HOC SINH =====\n";
    NodeHS* temp = headHS;

    while (temp) {
        cout << "MSHS: " << temp->data.mshs 
             << " | Ten: " << temp->data.ten
             << " | Lop: " << temp->data.lop
             << " | User: " << temp->data.tenDN
             << " | Diem: " << temp->data.diem << endl;
        temp = temp->next;
    }
}


void QuanLy::menuGiaoVien() {
    clearScreen();
    int lua;

    do {
        setColor(14);
        cout << "\n===== MENU GIAO VIEN =====\n";
        setColor(6);
        cout << "1. Them hoc sinh\n";
        cout << "2. Xoa hoc sinh\n";
        cout << "3. Dat thoi gian thi\n";
        cout << "4. Tao cau hoi\n";
        cout << "5. Xem danh sach hoc sinh\n";
        cout << "0. Quay lai\n";
        setColor(7);

        cout << "Chon: ";
        cin >> lua;

        while (cin.fail() || lua < 0 || lua > 5) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Lua chon khong hop le Vui long chon lai (0 - 5): ";
            cin >> lua;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

        switch (lua) {
            case 1: themHocSinh(); break;
            case 2:
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  
    xoaHocSinh();
    break;

            case 3: datThoiGianThi(); break;
            case 4: taoCauHoi(); break;
            case 5: xemDSHocSinh(); break;
        }
    } while (lua != 0);
}



// ================= MENU HOC SINH =================
void QuanLy::lamBaiThi(string user) {
    if (!headCH) {
        cout << "Chua co cau hoi nao!\n";
        return;
    }

    int dung = 0, socau = 0;
    char ans;
    NodeCH* temp = headCH;

    while (temp) {
        socau++;
        cout << "\nCau " << socau << ": " << temp->data.noiDung << endl;
        cout << "A. " << temp->data.a << endl;
        cout << "B. " << temp->data.b << endl;
        cout << "C. " << temp->data.c << endl;
        cout << "D. " << temp->data.d << endl;

        cout << "Chon: ";
        cin >> ans;

        while (toupper(ans) < 'A' || toupper(ans) > 'D') {
            cout << "Lua chon khong hop le! Chi duoc chon A, B, C hoac D.\n";
            cout << "Nhap lai: ";
            cin >> ans;
        }

        if (toupper(ans) == toupper(temp->data.dapAnDung))
            dung++;

        temp = temp->next;
    }

    float diem = (float)dung / socau * 10;
    cout << "\nDiem cua ban: " << diem << endl;

    NodeHS* hs = headHS;
    while (hs) {
        if (hs->data.tenDN == user) {
            hs->data.diem = diem;
            break;
        }
        hs = hs->next;
    }
}

void QuanLy::menuHocSinh(HocSinh* hs) {
    clearScreen();
    int lua;

    do {
        setColor(13);
        cout << "\n===== MENU HOC SINH =====\n";
        setColor(5);
        cout << "1. Lam bai thi\n";
        cout << "0. Quay lai\n";
        setColor(7);

        cout << "Chon: ";
        cin >> lua;

        while (cin.fail() || lua < 0 || lua > 1) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Lua chon khong hop le! Vui long chon lai (0 - 1): ";
            cin >> lua;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

        if (lua == 1)
            lamBaiThi(hs->tenDN);

    } while (lua != 0);
}

bool QuanLy::dangNhapAdmin() {
    string user, pass;
    for (int i = 0; i < 3; i++) {
        cout << "\n===== DANG NHAP ADMIN =====\n";
        cout << "Ten dang nhap: "; cin >> user;
        cout << "Mat khau: "; cin >> pass;
        if (user == "admin" && pass == "123") return true;
        cout << "Sai Con " << 2 - i << " lan.\n";
    }
    return false;
}

GiaoVien* QuanLy::dangNhapGV() {
    string user, pass;
    for (int i = 0; i < 3; i++) {
        cout << "\n===== DANG NHAP GV =====\n";
        cout << "Ten dang nhap: "; cin >> user;
        cout << "Mat khau: "; cin >> pass;

        NodeGV* temp = headGV;
        while (temp) {
            if (temp->data.tenDN == user && temp->data.matKhau == pass)
                return &temp->data;
            temp = temp->next;
        }
        cout << "Sai! Con " << 2 - i << " lan.\n";
    }
    return NULL;
}

HocSinh* QuanLy::dangNhapHS() {
    string user, pass;
    for (int i = 0; i < 3; i++) {
        cout << "\n===== DANG NHAP HS =====\n";
        cout << "Ten dang nhap: "; cin >> user;
        cout << "Mat khau: "; cin >> pass;

        NodeHS* temp = headHS;
        while (temp) {
            if (temp->data.tenDN == user && temp->data.matKhau == pass)
                return &temp->data;
            temp = temp->next;
        }
        cout << "Sai! Con " << 2 - i << " lan.\n";
    }
    return NULL;
}

// ================= MAIN =================
int main() {
    QuanLy ql;
    int chon;

    do {
        clearScreen();

        setColor(11);
        cout << "\n============================================================\n";
        cout << "||                                       (\\__/)           || \n";
        cout << "||           CHAO MUNG BAN DEN VOI APP   ( ^_^)/          || \n";
        cout << "||                                       /   |            ||\n";
        cout << "============================================================\n";

        setColor(9);  cout << "1. Dang nhap ADMIN\n";
        setColor(14); cout << "2. Dang nhap GIAO VIEN\n";
        setColor(13); cout << "3. Dang nhap HOC SINH\n";
        setColor(12); cout << "0. Thoat\n";

        setColor(11);
        cout << "Chon: ";
        setColor(7);
        cin >> chon;
        while (cin.fail() || chon < 0 || chon > 3) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Lua chon khong hop le. Vui long chon lai (0 - 3): ";
            cin >> chon;
        }

        switch (chon) {

        case 1:
            clearScreen();
            setColor(9);
            if (ql.dangNhapAdmin()) ql.menuAdmin();
            else cout << "Nhap sai 3 lan\n";
            break;

        case 2:
            clearScreen();
            setColor(14);

            if (!ql.headGV) {
                cout << "Chua co giao vien. Vui long them giao vien truoc\n";
                Sleep(1500);
                break;      
            }

            {
                GiaoVien* gv = ql.dangNhapGV();
                if (gv) ql.menuGiaoVien();
                else cout << "Nhap sai 3 lan\n";
            }
            break;

        case 3:
            clearScreen();
            setColor(13);

            if (!ql.headHS) {
                cout << "Chua co hoc sinh. Vui long them hoc sinh truoc\n";
                Sleep(1500);
                break;      
            }

            {
                HocSinh* hs = ql.dangNhapHS();
                if (hs) ql.menuHocSinh(hs);
                else cout << "Nhap sai 3 lan\n";
            }
            break;

        } 

        setColor(7);

    } while (chon != 0);

    cout << "Tam biet!\n";
    return 0;
}


