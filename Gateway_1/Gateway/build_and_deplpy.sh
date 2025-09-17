#!/bin/bash

# =============================
# Cấu hình
# =============================
REMOTE_USER="root"                         # Thay bằng tên người dùng trên thiết bị từ xa
REMOTE_HOST="192.168.1.5"                  # IP hoặc hostname
REMOTE_PATH="/usr/send_to_sg2002_3"        # Thư mục đích

# =============================
# Bước 0: Xóa file sexy_app nếu đã tồn tại
# =============================
if [ -f "sexy_app" ]; then
    echo "[+] Đã tìm thấy file sexy_app cũ. Đang xóa..."
    rm -f sexy_app
    echo "[+] Đã xóa file cũ."
fi

# =============================
# Bước 1: Compile file Go
# =============================
echo "[+] Đang compile file Go..."

GOOS=linux GOARCH=riscv64 CGO_ENABLED=1 \
CC=$RISCV_MUSL/riscv64-unknown-linux-musl-gcc \
go build -o sexy_app main.go mainpage.go Test_socket.go normalize_type_for_columns_and_values.go login_register.go dbclass.go add_node.go add_node_post_dealing.go check_authentication.go decode_payload.go split_authentication_from_decoded_payload.go handle_upcoming_data_uplink.go mqtt_publish_data.go

if [ $? -ne 0 ]; then
    echo "[!] Compile thất bại!"
    exit 1
fi

echo "[+] Compile thành công! File: sexy_app"

# =============================
# Bước 2: Hỏi người dùng
# =============================
read -p "Bạn có muốn gửi file qua thiết bị khác không? (y/n): " answer

# =============================
# Bước 3: Xử lý câu trả lời
# =============================
if [[ "$answer" == "y" || "$answer" == "Y" ]]; then
    echo "[+] Đang gửi file qua thiết bị..."
    scp sexy_app "$REMOTE_USER@$REMOTE_HOST:$REMOTE_PATH"

    if [ $? -eq 0 ]; then
        echo "[+] Gửi thành công!"
    else
        echo "[!] Gửi thất bại!"
    fi

elif [[ "$answer" == "n" || "$answer" == "N" ]]; then
    echo "[+] Đã chọn không gửi file. Kết thúc script."
    exit 0
else
    echo "[!] Câu trả lời không hợp lệ. Dừng script."
    exit 1
fi
