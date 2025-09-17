#include <Work_with_bytes/interval_format.h>


int parse_time_string(const char *input, uint8_t *output) {
    // Kiểm tra định dạng chuỗi: phải chính xác "xx yy zz aa" với khoảng trắng phân cách
    if (!input || input[2] != ' ' || input[5] != ' ' || input[8] != ' ' || input[11] != '\0') {
        return -1;
    }

    // Chuyển các phần số thập phân sang byte
    for (int i = 0, out_idx = 0; i < 11; i += 3, out_idx++) {
        // Kiểm tra nếu các ký tự là số từ 0 đến 9 bằng cách kiểm tra mã ASCII
        if (input[i] < '0' || input[i] > '9' || input[i + 1] < '0' || input[i + 1] > '9') {
            return -1;
        }
        // Chuyển từ chuỗi số thập phân thành giá trị số
        int value = (input[i] - '0') * 10 + (input[i + 1] - '0');
        output[out_idx] = (uint8_t)value;
    }
    return 0;
}
