
console.log(" hello ");


document.addEventListener("DOMContentLoaded", function () {
    const submitButton = document.getElementById("submit_button");

    submitButton.addEventListener("click", function (event) {
        event.preventDefault(); // Ngăn form gửi mặc định

        const username = document.getElementById("user_id_input").value;
        const password = document.getElementById("password_input").value;
        const rememberme = document.getElementById("user-check").checked ? 1 : 0;

        // Kiểm tra input không rỗng
        if (!username || !password) {
            alert("Vui lòng nhập tài khoản và mật khẩu!");
            return;
        }
        console.log(username)
        console.log(password)
        console.log(rememberme)

        fetch("http://192.168.1.5:8081/login_request", {
            method: "POST",
            body: JSON.stringify({
                username: username,
                password: password,
                rememberme: rememberme
            }),
            headers: {
                "Content-Type": "application/json; charset=UTF-8"
            }
        })
        .then(response => response.json())
        .then(data => {
            console.log("Server Responseeeeeeeeeeeeeeee:", data);

                
             //   window.location.href = "/dashboard"; // Điều hướng nếu đăng nhập thành công
          
        })
        .catch(error => console.error("Lỗi:", error));
    });
});
