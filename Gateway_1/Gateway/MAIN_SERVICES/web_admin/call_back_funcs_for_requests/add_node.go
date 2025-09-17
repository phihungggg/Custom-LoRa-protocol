package call_back_funcs_for_requests

import (
	"net/http"

	"github.com/gin-gonic/gin"
	//"crypto/rand"
	"database/sql"
	"example/SIDE_SERVICE/random_bsht_libs"
	"fmt"
	"log"

	_ "github.com/mattn/go-sqlite3"

	"example/SIDE_SERVICE/n_database_deal/db_class"
)

type NodeInfo struct {
	ID   int
	Name string
}

func Add_node_GET(c *gin.Context) {

	//generate AES byte

	AES_bytes, err := random_bsht_libs.GenerateRandomHex_n_Bytes(32)

	if err != nil {
		fmt.Println("Error generating random data:", err)
		return
	}

	AES_result := random_bsht_libs.ByteArrayToHexString(AES_bytes)
	fmt.Println("Random 32-byte hex string:", AES_result)

	//generate Address_byte

	Address_byte, err := random_bsht_libs.GenerateRandomHex_n_Bytes(2)

	if err != nil {
		fmt.Println("Error generating random data:", err)
		return
	}
	Address_result := random_bsht_libs.ByteArrayToHexString(Address_byte)

	// generate Authentication byte

	Authentication_byte, err := random_bsht_libs.GenerateRandomHex_n_Bytes(4)

	if err != nil {
		fmt.Println("Error generating random data:", err)
		return
	}
	Authentication_result := random_bsht_libs.ByteArrayToHexString(Authentication_byte)

	var nodes []NodeInfo
	{
		db := db_class.NewDatabase("sqlite3", "LoRa.db")
		driver := db.Get_driver()
		file := db.Get_database_file()
		db_final_object, err := sql.Open(driver, file)
		if err != nil {
			log.Fatal(err)
		}
		defer db_final_object.Close()

		Take_node_map_data_Stmt := `SELECT node_id, node_name FROM node_map;`
		rows, err := db_final_object.Query(Take_node_map_data_Stmt)
		if err != nil {
			fmt.Println(err.Error())
			return
		}
		defer rows.Close()

		for rows.Next() {
			var nodeID int
			var nodeName string
			if err := rows.Scan(&nodeID, &nodeName); err != nil {
				fmt.Println(err.Error())
				return
			}
			fmt.Println("node_id:", nodeID, "node_name:", nodeName)

			nodes = append(nodes, NodeInfo{
				ID:   nodeID,
				Name: nodeName,
			})
		}

	}
	
	data := gin.H{
		"AES_KEY":            AES_result,
		"Node_address":       Address_result,
		"AUTHENTICATION_KEY": Authentication_result,
		"Nodes":              nodes,
	}

	c.HTML(http.StatusOK, "add_node.html", data)

}
