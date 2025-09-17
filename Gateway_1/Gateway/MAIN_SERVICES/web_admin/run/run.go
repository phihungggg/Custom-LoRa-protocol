package run

import (

	//"fmt"
	//"github.com/gin-contrib/cors"
	"github.com/gin-gonic/gin"
)

func run_web() *gin.Engine {

	router := Get_router_ready()

	return router
}
