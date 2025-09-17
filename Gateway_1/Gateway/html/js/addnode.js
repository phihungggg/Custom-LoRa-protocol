
console.log("hello this is addnode");

document.addEventListener("DOMContentLoaded", function () {
  // ➤ In ra các giá trị được Gin truyền sẵn vào input
  const initNodeAddress = document.getElementById("node_address").value;
  const initAESKey = document.getElementById("aes_key").value;
  const initAuthKey = document.getElementById("auth_key").value;

  console.log("Initial Node Address:", initNodeAddress);
  console.log("Initial AES Key:", initAESKey);
  console.log("Initial Authentication Key:", initAuthKey);

  // Nút submit
  const submit_node_register_button = document.getElementById("submit_node_register_button");

  submit_node_register_button.addEventListener("click", function (event) {
    event.preventDefault(); // Prevent form from reloading the page

    // Get values from form fields (sau khi user nhập hoặc giữ nguyên)
    const node_id = document.getElementById("node_id").value.trim();
    const nodeSelect = document.getElementById("node_id");
    const selectedOption = nodeSelect.options[nodeSelect.selectedIndex];
    const node_name = selectedOption.getAttribute("data-name");
    console.log(" in thu node name ")
    console.log (node_name)

    const auth_key = document.getElementById("auth_key").value.trim();
    const node_address = document.getElementById("node_address").value.trim();
    const aes_key = document.getElementById("aes_key").value.trim();
    const is_ack_needed = document.getElementById("is_ack_needed").value;

    const ping_days = document.querySelector("select[name='ping_days']").value;
    const ping_hours = document.querySelector("select[name='ping_hours']").value;
    const ping_minutes = document.querySelector("select[name='ping_minutes']").value;
    const ping_seconds = document.querySelector("select[name='ping_seconds']").value;


    // Basic AES Key format validation (32 hex characters = 16 bytes)
    let normalized = aes_key.replace(/0x/g, "").replace(/,/g, "");
    console.log(normalized)
    const hexPattern = /^[0-9A-Fa-f]{64}$/;
    if (!hexPattern.test(normalized)) {
      alert("AES Key must be exactly 32 hexadecimal characters (16 bytes).");
      return;
    }
  
  

    // Combine all data
    const data = {
      node_id,
      node_address,
      aes_key,
      auth_key,
      is_ack_needed,
      ping_interval: {
        days: parseInt(ping_days),
        hours: parseInt(ping_hours),
        minutes: parseInt(ping_minutes),
        seconds: parseInt(ping_seconds),
      },
      node_name,
    };
    
    console.log("node id:", data.node_id);
    console.log("node_address:", data.node_address);
    console.log("aes_key:", data.aes_key);
    console.log("auth_key:", data.auth_key);
    
    console.log("is_ack_needed:", data.is_ack_needed);
    console.log("ping days:",  data.ping_interval.days);
    console.log("ping hours:", data.ping_interval.hours);
    console.log("ping minutes:", data.ping_interval.minutes);
    console.log("ping seconds:", data.ping_interval.seconds);

    // Send the data to your backend (adjust URL if needed)
    fetch("http://192.168.1.5:8081/add_node_request", {
      method: "POST",
      headers: {
        "Content-Type": "application/json"
      },
      body: JSON.stringify(data)
    })
    .then(response => {
      if (response.ok) {
        alert("Node successfully added!");
        // Optionally reset form here
      } else {
        alert("Failed to add node. Please try again.");
      }
    })
    .catch(error => {
      console.error("Error:", error);
      alert("Something went wrong while sending data.");
    });
  });
});
