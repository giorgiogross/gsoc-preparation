import React from "react";
import {render} from "react-dom";

import {Header} from "./components/Header"
import {Home} from "./components/Home"

class App extends React.Component {
    render() {
        var user = {
            name: "Uasername",
            hobbies: ["Swimming", "Climbing"]
        };
        return (

            // only one parent element is allowed here
            // use className instead oof class; add some bootstrap here
            <div className="container">
                <div className="row">
                    <div className="col-xs-10 col-xs-offset-1">
                        <Header/>
                    </div>
                </div>
                <div className="row">
                    <div className="col-xs-10 col-xs-offset-1">
                        <Home name={"John"} age={30} user={user}>
                            <p>This is some HTML code passed as a prop to the props.children of the Home class.
                                props.children is a reserved word</p>
                        </Home>
                    </div>
                </div>
            </div>
        );
    }
}

render(<App/>, window.document.getElementById("root"));