#include <unordered_map>
#include <cstring>
#include <string>
using namespace std;
class Bitmap {
private:
    mutable string M;  // 位图空间 M[]，允许在 const 成员函数中修改
    mutable int N, _sz; // 位图的大小和有效位的数量，允许在 const 成员函数中修改

protected:
    void init(int n) {
        N = n;  // 位图的有效位数
        M = string(n, '0');  // 初始化为 '0'
        _sz = 0;  // 初始化有效位数
    }

public:
    // 默认构造函数，按指定容量创建位图（默认8个比特位）
    Bitmap(int n = 8) {
        init(n);
    }

    // 从文件读取位图并初始化
    Bitmap(const string& file, int n = 8) {
        init(n);
        FILE* fp = fopen(file.c_str(), "rb");
        if (fp) {
            fread(&M[0], sizeof(char), N, fp);  // 读取文件内容到位图
            fclose(fp);
            // 统计文件中已设置的有效位数
            for (int k = 0; k < n; k++) {
                if (test(k)) _sz++;
            }
        }
    }

    // 获取位图大小
    int size() const {
        return _sz;
    }

    // 设置指定位置k的位为1
    void set(int k) {
        expand(k);
        _sz++;
        M[k] = '1';
    }

    // 清除指定位置k的位
    void clear(int k) {
        expand(k);
        _sz--;
        M[k] = '0';
    }

    // 测试指定位置k的位是否为1
    bool test(int k)  {
        expand(k);
        return M[k] == '1';
    }

    // 将位图导出至文件
    void dump(const string& file) const {
        FILE* fp = fopen(file.c_str(), "wb");
        if (fp) {
            fwrite(&M[0], sizeof(char), N, fp);  // 将位图写入文件
            fclose(fp);
        }
    }

    // 将前n位转换为字符串
    string bits2string(int n) const {
        expand(n - 1);  // 确保扩展位图以适应 n 位
        return M.substr(0, n);  // 返回前n个字符
    }

    // 将二进制字符串转换为位图
    void fromBinaryString(const string& binStr) {
        init(binStr.length());
        M = binStr;  // 直接将二进制字符串赋给位图
        _sz = binStr.length();  // 有效位数为字符串长度
    }

private:
    // 如果k超出当前位图的范围，则扩展位图
    void expand(int k) const {
        if (k < N) return;  // 位图没有超出界限，无需扩展
        N = k + 1;
        M.resize(N, '0');  // 扩展位图并初始化为 '0'
    }
};

