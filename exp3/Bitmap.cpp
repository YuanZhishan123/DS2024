#include <unordered_map>
#include <cstring>
#include <string>
using namespace std;
class Bitmap {
private:
    mutable string M;  // λͼ�ռ� M[]�������� const ��Ա�������޸�
    mutable int N, _sz; // λͼ�Ĵ�С����Чλ�������������� const ��Ա�������޸�

protected:
    void init(int n) {
        N = n;  // λͼ����Чλ��
        M = string(n, '0');  // ��ʼ��Ϊ '0'
        _sz = 0;  // ��ʼ����Чλ��
    }

public:
    // Ĭ�Ϲ��캯������ָ����������λͼ��Ĭ��8������λ��
    Bitmap(int n = 8) {
        init(n);
    }

    // ���ļ���ȡλͼ����ʼ��
    Bitmap(const string& file, int n = 8) {
        init(n);
        FILE* fp = fopen(file.c_str(), "rb");
        if (fp) {
            fread(&M[0], sizeof(char), N, fp);  // ��ȡ�ļ����ݵ�λͼ
            fclose(fp);
            // ͳ���ļ��������õ���Чλ��
            for (int k = 0; k < n; k++) {
                if (test(k)) _sz++;
            }
        }
    }

    // ��ȡλͼ��С
    int size() const {
        return _sz;
    }

    // ����ָ��λ��k��λΪ1
    void set(int k) {
        expand(k);
        _sz++;
        M[k] = '1';
    }

    // ���ָ��λ��k��λ
    void clear(int k) {
        expand(k);
        _sz--;
        M[k] = '0';
    }

    // ����ָ��λ��k��λ�Ƿ�Ϊ1
    bool test(int k)  {
        expand(k);
        return M[k] == '1';
    }

    // ��λͼ�������ļ�
    void dump(const string& file) const {
        FILE* fp = fopen(file.c_str(), "wb");
        if (fp) {
            fwrite(&M[0], sizeof(char), N, fp);  // ��λͼд���ļ�
            fclose(fp);
        }
    }

    // ��ǰnλת��Ϊ�ַ���
    string bits2string(int n) const {
        expand(n - 1);  // ȷ����չλͼ����Ӧ n λ
        return M.substr(0, n);  // ����ǰn���ַ�
    }

    // ���������ַ���ת��Ϊλͼ
    void fromBinaryString(const string& binStr) {
        init(binStr.length());
        M = binStr;  // ֱ�ӽ��������ַ�������λͼ
        _sz = binStr.length();  // ��Чλ��Ϊ�ַ�������
    }

private:
    // ���k������ǰλͼ�ķ�Χ������չλͼ
    void expand(int k) const {
        if (k < N) return;  // λͼû�г������ޣ�������չ
        N = k + 1;
        M.resize(N, '0');  // ��չλͼ����ʼ��Ϊ '0'
    }
};

