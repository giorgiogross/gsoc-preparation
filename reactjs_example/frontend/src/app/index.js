import React from "react";
import {render} from "react-dom";

import {Header} from "./components/Header"
import {Home} from "./components/Home"

class App extends React.Component {
    constructor() {
        super();
        this.state = {
            homeLink: "Home"
        }
    }

    functionWhichIsCalledByChild() {
        alert("Hello");
    }

    onRenameHomeLink(newName) {
        this.setState({
            homeLink: newName
        });
    }

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
                        <Header homeLink={this.state.homeLink}/>
                    </div>
                </div>
                <div className="row">
                    <div className="col-xs-10 col-xs-offset-1">
                        <Home name={"John"}
                              initialAge={30}
                              user={user}
                              functionCallback={this.functionWhichIsCalledByChild}
                              initialLink={this.state.homeLink} 
                              changeLink={this.onRenameHomeLink.bind(this)}>
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