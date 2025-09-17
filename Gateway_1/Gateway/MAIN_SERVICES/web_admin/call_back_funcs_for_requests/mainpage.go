package call_back_funcs_for_requests

import (
	"net/http"

	"github.com/gin-gonic/gin"
)

func GetMainpage(c *gin.Context) {
	c.HTML(http.StatusOK, "firstpage.html", nil)

}
