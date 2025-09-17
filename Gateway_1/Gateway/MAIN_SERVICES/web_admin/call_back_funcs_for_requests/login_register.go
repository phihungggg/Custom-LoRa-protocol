package call_back_funcs_for_requests

import (
	"database/sql"
	"example/MAIN_SERVICES/web_admin/auth"
	"example/SIDE_SERVICE/n_database_deal"
	"example/SIDE_SERVICE/n_database_deal/n_enum_database_deal/user_data_enum"
	"fmt"
	"log"
	"net/http"

	"github.com/gin-gonic/gin"
)

type LoginData struct {
	UserID             string `json:"username" binding:"required"`
	Password           string `json:"password" binding:"required"`
	Remember_the_login int    `json:"rememberme" biding:"required" `
}

func PostDealing(c *gin.Context) {
	fmt.Printf(" post dealing function ? ")
	var login LoginData
	if err := c.ShouldBindJSON(&login); err != nil {
		c.JSON(http.StatusBadRequest, gin.H{"error": err.Error()})
		return
	}
	db_final_object, err := sql.Open("sqlite3", "LoRa.db")
	if err != nil {

		fmt.Print(" loi cac gi vay \n")

		log.Fatal(err)
		return
	}
	defer db_final_object.Close()

	var username, id, role string
	//errr := n_database_deal.Action_to_database_CRUD(&username,&id,&role ,"user", db.get_database_file(), db.get_driver(), n_enum.Read, []string{"username", "password"}, login.UserID, login.Password)
	columns_count, data, errr := n_database_deal.Take_every_row_match_those_input(db_final_object, "user", []string{"username", "password"}, login.UserID, login.Password)
	if errr != nil || columns_count != len((*data)[0]) {
		fmt.Println(" \nco loi o vi tri cuoi cung")
		fmt.Printf(errr.Error())
		c.JSON(http.StatusBadRequest, gin.H{"message": "Login failed"})
		return
	}
	username = (*data)[0][user_data_enum.USERNAME_OF_USER]
	role = (*data)[0][user_data_enum.ROLE_OF_USER]
	id = (*data)[0][user_data_enum.ID_OF_USER]
	fmt.Println(" gio print thu user name , role , id \n")
	fmt.Printf(" role la %s\n", role)
	fmt.Printf(" username la %s\n", username)
	fmt.Printf("  id la %s\n", id)
	tokenString, err2 := auth.CreateToken(username, role, id)

	if err2 != nil {
		c.String(http.StatusInternalServerError, "Error creating token")
		return
	}
	c.SetCookie("token", tokenString, 3600, "/login_request", "localhost", false, true)

	c.JSON(http.StatusOK, gin.H{"message": "Login successful"})

}
