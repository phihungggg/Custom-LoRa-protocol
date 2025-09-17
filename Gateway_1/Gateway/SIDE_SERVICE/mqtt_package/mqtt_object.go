package mqtt_package

import (
	"crypto/tls"
	"fmt"
	"log"
	"os"
	"time"

	mqtt "github.com/eclipse/paho.mqtt.golang"
)

var callback mqtt.MessageHandler = func(client mqtt.Client, message mqtt.Message) {

}

type Mqtt_object struct {
	broker_uri string
	client_id  string
	username   string
	password   string

	is_init_mqtt_yet bool

	mqtt_client mqtt.Client
	mqtt_token  mqtt.Token

	topic []string

	data interface{}
}

func (m *Mqtt_object) Set_data(data interface{}) {

	m.data = data

}

func (m *Mqtt_object) Mqtt_init(broker_uri, client_id, username, password string) {

	mqtt.DEBUG = log.New(os.Stdout, "", 0)
	mqtt.ERROR = log.New(os.Stdout, "", 0)

	m.broker_uri = broker_uri

	m.client_id = client_id

	m.password = password

	m.username = username

	danchoi_mqtt := mqtt.NewClientOptions().AddBroker(m.broker_uri).
		SetClientID(m.client_id).
		SetUsername(m.username).
		SetPassword(m.password)

	danchoi_mqtt.SetTLSConfig(&tls.Config{
		InsecureSkipVerify: true,
	})

	danchoi_mqtt.SetKeepAlive(60 * time.Second)

	danchoi_mqtt.SetDefaultPublishHandler(callback)
	danchoi_mqtt.SetPingTimeout(1 * time.Second)

	m.mqtt_client = mqtt.NewClient(danchoi_mqtt)

	if m.mqtt_token = m.mqtt_client.Connect(); m.mqtt_token.Wait() && m.mqtt_token.Error() != nil {
		panic(m.mqtt_token.Error())
	}

	m.is_init_mqtt_yet = true

}

func (m *Mqtt_object) Mqtt_do_mqtt_things(topic string) {

	if m.is_init_mqtt_yet == false {

		fmt.Printf("  you haven't init mqtt object , please init it  \n")
		return
	}

	m.topic = append(m.topic, topic)

	m.mqtt_token = m.mqtt_client.Publish(m.topic[0], 0, false, m.data)

	m.mqtt_token.Wait()

	m.mqtt_client.Disconnect(100)

	//	time.Sleep(6 * time.Second)

	//	you_mother.Disconnect(250)

	//	time.Sleep(1 * time.Second)

}
