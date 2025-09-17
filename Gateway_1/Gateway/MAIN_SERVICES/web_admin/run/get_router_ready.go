package run

import (
	"example/MAIN_SERVICES/web_admin/call_back_funcs_for_requests"

	"github.com/gin-gonic/gin"

	"github.com/gin-contrib/cors"
)

func Get_router_ready() *gin.Engine {

	router := gin.Default()

	router.Use(cors.New(cors.Config{
		AllowOrigins:     []string{"http://0.0.0.0:8081"},
		AllowMethods:     []string{"POST", "GET", "OPTIONS"},
		AllowHeaders:     []string{"Origin", "Content-Type"},
		AllowCredentials: true,
	}))

	// Load HTML template
	router.LoadHTMLFiles("html/firstpage.html", "html/login.html", "html/showinformation.html", "html/add_node.html")
	// Serve static files (CSS, images)
	router.Static("/static", "./html")
	router.GET("/", call_back_funcs_for_requests.GetMainpage)
	//router.GET("/node_name", get_Node_name)
	//router.GET("/values_temperature_humidity", get_Values)
	//router.GET("/login", get_Values)

	router.GET("/information_test", call_back_funcs_for_requests.Test_socket)
	router.GET("/add_node_get", call_back_funcs_for_requests.Add_node_GET)
	router.POST("/add_node_request", call_back_funcs_for_requests.Add_node_Dealing)
	router.POST("/login_request", call_back_funcs_for_requests.PostDealing)

	return router

}
