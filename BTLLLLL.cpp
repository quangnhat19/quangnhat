#include <iostream>
#include <string>
#include <cctype>
using namespace std;

// ==================== MA MAU ANSI ====================
#define RESET "\033[0m"
#define FG_WHITE "\033[97m"
#define FG_BLACK "\033[30m"
#define BG_WHITE "\033[107m"
#define BG_BLACK "\033[40m"

// ==================== CAU TRUC DU LIEU ====================
struct CauHoi {
    string noiDung, a, b, c, d;
    char dapAnDung;
};

struct HocSinh {
    string tenDN, matKhau, ten, lop;
    float diem = 0;
};

struct GiaoVien {
    string tenDN, matKhau, ten, mon, lopPhuTrach;
};

struct NodeGV { GiaoVien data; NodeGV* next; };
struct NodeHS { HocSinh data; NodeHS* next; };
struct NodeCH { CauHoi data; NodeCH* next; };

// ==================== LOP QUAN LY ====================
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

// ==================== CAC HAM HO TRO ====================
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
            if (prev) prev->next = temp->next; else head = temp->next;
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
            if (prev) prev->next = temp->next; else head = temp->next;
            delete temp; return true;
        }
        prev = temp; temp = temp->next;
    }
    return false;
}

// ==================== CHUC NANG ADMIN ====================
void QuanLy::themGiaoVien() {
    int n;
    cout << "Nhap so luong giao vien muon them: ";
    while (!(cin >> n) || n <= 0) {
        cout << "Nhap lai so nguyen duong: ";
        cin.clear(); cin.ignore(10000, '\n');
    }
    cin.ignore();

    for (int i = 0; i < n; i++) {
        GiaoVien gv;
        cout << "\n=== GIAO VIEN " << i + 1 << " ===\n";
        cout << "Ten dang nhap: "; getline(cin, gv.tenDN);
        cout << "Mat khau: "; getline(cin, gv.matKhau);
        cout << "Ten giao vien: "; getline(cin, gv.ten);
        cout << "Mon day: "; getline(cin, gv.mon);
        cout << "Lop phu trach: "; getline(cin, gv.lopPhuTrach);
        themCuoiGV(headGV, gv);
    }
    cout << "\nDa them " << n << " giao vien thanh cong!\n";
}

void QuanLy::xoaGiaoVien() {
    string user;
    cin.ignore();
    cout << "Nhap ten dang nhap giao vien can xoa: ";
    getline(cin, user);
    cout << (xoaGV(headGV, user) ? "Da xoa giao vien!\n" : "Khong tim thay giao vien!\n");
}

void QuanLy::xemDSGiaoVien() {
    cout << "\n=== DANH SACH GIAO VIEN ===\n";
    NodeGV* temp = headGV;
    while (temp) {
        cout << "Ten: " << temp->data.ten << " | Mon: " << temp->data.mon
             << " | Lop: " << temp->data.lopPhuTrach << endl;
        temp = temp->next;
    }
}

void QuanLy::menuAdmin() {
    int lua;
    do {
        cout << "\n=== MENU ADMIN ===\n";
        cout << "1. Them giao vien\n2. Xoa giao vien\n3. Xem danh sach giao vien\n0. Quay lai\nChon: ";
        if (!(cin >> lua)) { cin.clear(); cin.ignore(10000, '\n'); continue; }

        switch (lua) {
            case 1: themGiaoVien(); break;
            case 2: xoaGiaoVien(); break;
            case 3: xemDSGiaoVien(); break;
            case 0: break;
            default: cout << "Khong hop le!\n";
        }
    } while (lua != 0);
}

// ==================== CHUC NANG GIAO VIEN ====================
void QuanLy::themHocSinh() {
    int n;
    cout << "Nhap so luong hoc sinh muon them: ";
    while (!(cin >> n) || n <= 0) {
        cout << "Nhap lai so nguyen duong: ";
        cin.clear(); cin.ignore(10000, '\n');
    }
    cin.ignore();

    for (int i = 0; i < n; i++) {
        HocSinh hs;
        cout << "\n=== HOC SINH " << i + 1 << " ===\n";
        cout << "Ten dang nhap: "; getline(cin, hs.tenDN);
        cout << "Mat khau: "; getline(cin, hs.matKhau);
        cout << "Ten hoc sinh: "; getline(cin, hs.ten);
        cout << "Lop: "; getline(cin, hs.lop);
        themCuoiHS(headHS, hs);
    }
    cout << "\nDa them " << n << " hoc sinh thanh cong!\n";
}

void QuanLy::xoaHocSinh() {
    string user;
    cout << "Nhap ten dang nhap hoc sinh can xoa: ";
    cin.ignore();
    getline(cin, user);
    if (xoaHS(headHS, user))
        cout << "? Da xoa hoc sinh!\n";
    else
        cout << "? Khong tim thay hoc sinh!\n";
}

void QuanLy::datThoiGianThi() {
    cout << "Nhap thoi gian lam bai (phut): ";
    cin >> thoiGianThi;
    cout << "? Da cai dat thoi gian " << thoiGianThi << " phut.\n";
}

void QuanLy::taoCauHoi() {
    int n;
    cout << "Nhap so luong cau hoi muon tao: ";
    cin >> n; cin.ignore();
    for (int i = 0; i < n; i++) {
        CauHoi ch;
        cout << "\nNhap noi dung cau hoi: "; getline(cin, ch.noiDung);
        cout << "A: "; getline(cin, ch.a);
        cout << "B: "; getline(cin, ch.b);
        cout << "C: "; getline(cin, ch.c);
        cout << "D: "; getline(cin, ch.d);
        cout << "Dap an dung (A/B/C/D): "; cin >> ch.dapAnDung; cin.ignore();
        themCuoiCH(headCH, ch);
    }
    cout << "\n? Da tao bo cau hoi thanh cong!\n";
}

void QuanLy::xemDSHocSinh() {
    cout << "\n===== DANH SACH HOC SINH =====\n";
    NodeHS* temp = headHS;
    while (temp) {
        cout << "Ten: " << temp->data.ten
             << " | Lop: " << temp->data.lop
             << " | Diem: " << temp->data.diem << endl;
        temp = temp->next;
    }
}

// ==================== MENU GIAO VIEN ====================
void QuanLy::menuGiaoVien() {
    int lua;
    do {
        cout << "\n===== MENU GIAO VIEN =====\n";
        cout << "1. Them hoc sinh\n";
        cout << "2. Xoa hoc sinh\n";
        cout << "3. Dat thoi gian thi\n";
        cout << "4. Tao cau hoi\n";
        cout << "5. Xem danh sach hoc sinh\n";
        cout << "0. Quay lai\n";
        cout << "Chon: ";

        if (!(cin >> lua)) {                   
            cout << "Lua chon khong hop le! Vui long nhap so.\n";
            cin.clear();                       
            cin.ignore(10000, '\n');           
            continue;                          
        }

        switch (lua) {
        case 1: themHocSinh(); break;
        case 2: xoaHocSinh(); break;
        case 3: datThoiGianThi(); break;
        case 4: taoCauHoi(); break;
        case 5: xemDSHocSinh(); break;
        case 0: break;
        default:
            cout << "Khong co lua chon nay! Vui long nhap lai.\n";
        }

    } while (lua != 0);
}

// ==================== CHUC NANG HOC SINH ====================
void QuanLy::lamBaiThi(string user) {
    if (!headCH) {
        cout << "? Chua co cau hoi nao!\n";
        return;
    }

    int dung = 0;
    char ans;
    NodeCH* temp = headCH;
    int i = 1;
    cout << "\n===== BAT DAU LAM BAI TRAC NGHIEM =====\n";
    while (temp) {
        cout << "\nCau " << i++ << ": " << temp->data.noiDung << endl;
        cout << "A. " << temp->data.a << endl;
        cout << "B. " << temp->data.b << endl;
        cout << "C. " << temp->data.c << endl;
        cout << "D. " << temp->data.d << endl;
        cout << "Chon dap an: ";
        cin >> ans;

        if (toupper(ans) == toupper(temp->data.dapAnDung))
            dung++;
        temp = temp->next;
    }

    float diem = (float)dung / (i - 1) * 10;
    cout << "\n? Hoan thanh! Diem cua ban: " << diem << endl;

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
    int lua;
    do {
        cout << "\n===== MENU HOC SINH =====\n";
        cout << "1. Lam bai thi\n";
        cout << "0. Quay lai\n";
        cout << "Chon: ";

        if (!(cin >> lua)) {                   
            cout << "Lua chon khong hop le! Vui long nhap so.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (lua) {
        case 1:
            lamBaiThi(hs->tenDN);
            break;
        case 0:
            break;
        default:
            cout << "Khong co lua chon nay! Vui long nhap lai.\n";
        }

    } while (lua != 0);
}

// ==================== ÐANG NHAP ====================
bool QuanLy::dangNhapAdmin() {
    string user, pass;
    for (int i = 0; i < 3; i++) {
        cout << "\n===== DANG NHAP ADMIN =====\n";
        cout << "Ten dang nhap: "; cin >> user;
        cout << "Mat khau: "; cin >> pass;
        if (user == "admin" && pass == "123") return true;
        cout << "Sai thong tin! Thu lai (" << 2 - i << " lan con lai)\n";
    }
    return false;
}

GiaoVien* QuanLy::dangNhapGV() {
    string user, pass;
    for (int i = 0; i < 3; i++) {
        cout << "\n===== DANG NHAP GIAO VIEN =====\n";
        cout << "Ten dang nhap: "; cin >> user;
        cout << "Mat khau: "; cin >> pass;
        NodeGV* temp = headGV;
        while (temp) {
            if (temp->data.tenDN == user && temp->data.matKhau == pass)
                return &temp->data;
            temp = temp->next;
        }
        cout << "Dang nhap sai! Thu lai (" << 2 - i << " lan con lai)\n";
    }
    return NULL;
}

HocSinh* QuanLy::dangNhapHS() {
    string user, pass;
    for (int i = 0; i < 3; i++) {
        cout << "\n===== DANG NHAP HOC SINH =====\n";
        cout << "Ten dang nhap: "; cin >> user;
        cout << "Mat khau: "; cin >> pass;
        NodeHS* temp = headHS;
        while (temp) {
            if (temp->data.tenDN == user && temp->data.matKhau == pass)
                return &temp->data;
            temp = temp->next;
        }
        cout << "Dang nhap sai! Thu lai (" << 2 - i << " lan con lai)\n";
    }
    return NULL;
}
bool cheDoToi = false; // false = sang, true = toi

void hienThiGiaoDien() {
    cout << RESET;
    if (cheDoToi) {
        cout << BG_BLACK << FG_WHITE;
        cout << "\n?? Da bat che do TOI!\n" << RESET;
    } else {
        cout << BG_WHITE << FG_BLACK;
        cout << "\n?? Da bat che do SANG!\n" << RESET;
    }
}

void chonGiaoDien() {
    int chon;
    cout  << "\n===== CHON GIAO DIEN =====\n" ;
    cout << "1. Che do SANG ??\n";
    cout << "2. Che do TOI ??\n";
    cout << "Chon: ";
    cin >> chon;
    cheDoToi = (chon == 2);
    hienThiGiaoDien();
}

// ==================== MAIN ====================
int main() {
    QuanLy ql;
    int chon;
    string giaoDien = "Sang"; 


    cout << "\n===== CHON GIAO DIEN =====\n";
    cout << "1. Giao dien sang\n";
    cout << "2. Giao dien toi\n";
    cout << "Chon: ";

    if (!(cin >> chon)) {
        cout << "Lua chon khong hop le! Mac dinh la giao dien sang.\n";
        cin.clear();
        cin.ignore(10000, '\n');
        chon = 1;
    }

    if (chon == 2) giaoDien = "Toi";
    cout << "\nBan da chon giao dien: " << giaoDien << "\n";

    // --- Menu chinh ---
    do {
        cout << "\n===== MENU CHINH (" << giaoDien << ") =====\n";
        cout << "1. Dang nhap ADMIN\n";
        cout << "2. Dang nhap GIAO VIEN\n";
        cout << "3. Dang nhap HOC SINH\n";
        cout << "4. Thay doi giao dien\n";
        cout << "0. Thoat\n";
        cout << "Chon: ";

        if (!(cin >> chon)) {
            cout << "Lua chon khong hop le! Vui long nhap so.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (chon) {
        case 1:
            if (ql.dangNhapAdmin()) ql.menuAdmin();
            else cout << "Ban da nhap sai 3 lan!\n";
            break;

        case 2:
            if (ql.headGV == NULL) {
                cout << "Chua co giao vien nao! Vui long them truoc khi dang nhap.\n";
                break;
            } else {
                GiaoVien* gv = ql.dangNhapGV();
                if (gv) ql.menuGiaoVien();
                else cout << "Ban da nhap sai 3 lan!\n";
            }
            break;

        case 3:
            if (ql.headHS == NULL) {
                cout << "Chua co hoc sinh nao! Vui long them truoc khi dang nhap.\n";
                break;
            } else {
                HocSinh* hs = ql.dangNhapHS();
                if (hs) ql.menuHocSinh(hs);
                else cout << "Ban da nhap sai 3 lan!\n";
            }
            break;

        case 4:
      
            if (giaoDien == "Sang") giaoDien = "Toi";
            else giaoDien = "Sang";
            cout << "Da chuyen sang giao dien: " << giaoDien << "\n";
            break;

        case 0:
            cout << "\nTam biet!\n";
            break;

        default:
            cout << "Khong co lua chon nay! Vui long nhap lai.\n";
        }

    } while (chon != 0);

    return 0;
}
