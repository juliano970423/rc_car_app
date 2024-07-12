import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import QtCore
import RemoteCar


Window {
    Material.theme: Material.Light
    Material.accent: Material.LightBlue
    width: 640
    height: 480
    visible: true
    title: qsTr("Rc car control")
    BluetoothPermission {
        id: bt_permission
        communicationModes: BluetoothPermission.Access
    }

    RemoteCar{
        id: remoteCarControl

    }

    Slider{
        id: speed_Slider
        height: parent.height/5*3
        width: parent.width/3
        anchors.verticalCenter: parent.verticalCenter
        stepSize: 1
        value:0
        from:0
        to:255
        orientation: Qt.Vertical
        onMoved:remoteCarControl.receiveMessage("f"+forward_backward.value+"s"+speed_Slider.value+"d"+direction_Slider.value)
    }
    Slider{
        id: forward_backward
        height:parent.height/5
        anchors.left: speed_Slider.right
        anchors.bottom: parent.bottom
        anchors.bottomMargin: parent.height/6
        value:1
        from:0
        to:1
        stepSize: 1
        snapMode: Slider.SnapAlways
        orientation: Qt.Vertical
        onMoved:remoteCarControl.receiveMessage("f"+forward_backward.value+"s"+speed_Slider.value+"d"+direction_Slider.value)
    }
    Slider{
        id: direction_Slider
        objectName: "direction_Slider"
        height: parent.height
        width: parent.width/3
        anchors.right: parent.right
        anchors.rightMargin: parent.width/10
        stepSize: 1
        value:90
        from:0
        to:180
        onMoved:remoteCarControl.receiveMessage("f"+forward_backward.value+"s"+speed_Slider.value+"d"+direction_Slider.value)
        onPressedChanged:function(){
            if(!direction_Slider.pressed){ //onRelease
                direction_Slider.value=90
                remoteCarControl.receiveMessage("f"+forward_backward.value+"s"+speed_Slider.value+"d"+direction_Slider.value)
            }
        }
    }
    Column{
        spacing: 5
        anchors.horizontalCenter: parent.horizontalCenter
        Row{
            spacing: 10
            anchors.horizontalCenter: parent.horizontalCenter
            TextField{
                id:bt_name
                text:"BT24"
                anchors.top: parent.top
                //anchors.right: bt_connect_button.left
                anchors.rightMargin: 5
            }

            Button{
                id:bt_connect_button
                text:"連接"
                anchors.top: parent.top
                //anchors.left: bt_name.right
                anchors.leftMargin: 5
                onClicked:function(){
                    remoteCarControl.connect_to_BT(bt_name.text)
                }
            }
        }
        Text {
            id: connect_state
            text: qsTr("未連接")
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }

    Connections{
        target: remoteCarControl
        onUpdateConnectingState:{
            //console.log("connection")
            connect_state.text=state
        }
    }
}
