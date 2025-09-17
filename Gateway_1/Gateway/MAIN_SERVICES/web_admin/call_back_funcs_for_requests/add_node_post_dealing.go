package call_back_funcs_for_requests

import (
	"fmt"
	"net/http"

	"github.com/gin-gonic/gin"

	"database/sql"
	"example/SIDE_SERVICE/n_database_deal"
	"example/SIDE_SERVICE/n_database_deal/db_class"
	"log"

	"math/big"

	_ "github.com/mattn/go-sqlite3"

	"crypto/rand"

	"strconv"
)

const charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"

type PingInterval struct {
	Days    int `json:"days"`
	Hours   int `json:"hours"`
	Minutes int `json:"minutes"`
	Seconds int `json:"seconds"`
}

type NodeRegisterData struct {
	NodeID       string       `json:"node_id" binding:"required"`
	NodeAddress  string       `json:"node_address" binding:"required"`
	AESKey       string       `json:"aes_key" binding:"required"`
	Auth_Key     string       `json:"auth_key" binding:"required"`
	IsAckNeeded  string       `json:"is_ack_needed" binding:"required"` // or `int`/`bool` if needed
	PingInterval PingInterval `json:"ping_interval" binding:"required"`
	NodeName     string       `json:"node_name" binding:"required"`
}

func Add_node_Dealing(c *gin.Context) {
	fmt.Println("Add_node_Dealing function called")
	var nodeinformation NodeRegisterData
	if err := c.ShouldBindJSON(&nodeinformation); err != nil {
		c.JSON(http.StatusBadRequest, gin.H{"error": err.Error()})
		return
	}

	db := db_class.NewDatabase("sqlite3", "LoRa.db")

	driver := db.Get_driver()
	file := db.Get_database_file()
	db_final_object, err := sql.Open(driver, file)

	if err != nil {
		log.Fatal(err)
	}
	defer db_final_object.Close()
	var errorMessage string
	node_id_int, err := strconv.Atoi(nodeinformation.NodeID)
	if err != nil {
		fmt.Println("Conversion error:", err)
		return
	} else {
		fmt.Println("Converted integer:", node_id_int)
	}
	err = n_database_deal.IF_that_data_have_in_database(db_final_object, "node_map", []string{"node_id"}, node_id_int)
	if err != nil {
		errorMessage = err.Error()
		fmt.Printf(errorMessage)
		return
	}

	fmt.Println(" have node id \n")

	fmt.Println(" add data to database \n")

	formatted_interval := fmt.Sprintf("%02d:%02d:%02d:%02d",
		nodeinformation.PingInterval.Days,
		nodeinformation.PingInterval.Hours,
		nodeinformation.PingInterval.Minutes,
		nodeinformation.PingInterval.Seconds,
	)

	ackBool := false

	if nodeinformation.IsAckNeeded == "Yes" {
		ackBool = true
	}

	insertStmt := `INSERT INTO node_list (node_id, ping_interval,node_address,AES_KEY,is_ack_needed) VALUES (?, ?,?,?,?)`

	_, errorr := db_final_object.Exec(insertStmt, nodeinformation.NodeID, formatted_interval, nodeinformation.NodeAddress, nodeinformation.AESKey, ackBool)

	if errorr != nil {
		errorMessage = errorr.Error()
		fmt.Printf(errorMessage)

	}

	insertStmt = `INSERT INTO node_authentication_key (node_address,Authentication_KEY) VALUES (?, ?)`

	_, errorr = db_final_object.Exec(insertStmt, nodeinformation.NodeAddress, nodeinformation.Auth_Key)

	if errorr != nil {
		errorMessage = errorr.Error()
		fmt.Printf(errorMessage)

	}

	

	table_request := ham_tao_chuoi_de_dan_toi_bang_can_thiet_CURRENT_STATE(nodeinformation.NodeName)

	fmt.Println(" in thu current state trong dealing")

	fmt.Println(table_request)

	insertStmt = fmt.Sprintf(`INSERT INTO %s (node_address, receive_date) VALUES (?, ?)`, table_request)

	_, errorr = db_final_object.Exec(insertStmt, nodeinformation.NodeAddress, "1970-01-01 00:00:00")

	if errorr != nil {
		errorMessage = errorr.Error()
		fmt.Printf(errorMessage)

	}

	//client_id := generatec_clientid(20)
	// add this later to node , thanks though
	insertStmt = `INSERT INTO mqtt_information () `
	fmt.Println("===== Node Information Received =====")
	fmt.Println("Node ID:        ", nodeinformation.NodeID)
	fmt.Println("Node Address:   ", nodeinformation.NodeAddress)
	fmt.Println("AES Key:        ", nodeinformation.AESKey)

	fmt.Println("Authentication Key        ", nodeinformation.Auth_Key)
	fmt.Println("Is ACK Needed:  ", nodeinformation.IsAckNeeded)
	fmt.Println("----- Ping Interval -----")
	fmt.Println("Days:    ", nodeinformation.PingInterval.Days)
	fmt.Println("Hours:   ", nodeinformation.PingInterval.Hours)
	fmt.Println("Minutes: ", nodeinformation.PingInterval.Minutes)
	fmt.Println("Seconds: ", nodeinformation.PingInterval.Seconds)
	c.JSON(http.StatusOK, gin.H{
		"message": "Node registered successfully!",
	})
}

func generatec_clientid(suffixLength int) string {
	const prefix = "greenstream"
	result := prefix

	for i := 0; i < suffixLength; i++ {
		num, _ := rand.Int(rand.Reader, big.NewInt(int64(len(charset))))
		result += string(charset[num.Int64()])
	}

	return result
}

func init_node_CURRENT_STATE_data() {

}

func ham_tao_chuoi_de_dan_toi_bang_can_thiet_CURRENT_STATE(input string) string {
	current_state := "_CURRENT_STATE"
	result := input + current_state
	return result
}
