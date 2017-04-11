import React from "react";
import {render} from "react-dom";
import {
    BrowserRouter as Router,
    Route,
    hashHistory
} from "react-router-dom"

import {Header} from "./components/Header"
import {Home} from "./components/Home"
import {User} from "./components/User"

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

    setUpHomeProps() {
        var user = {
            name: "Uasername",
            hobbies: ["Swimming", "Climbing"]
        };
        return (
            <Home
                name={"John"}
                initialAge={30}
                user={user}
                functionCallback={this.functionWhichIsCalledByChild}
                initialLink={this.state.homeLink}
                changeLink={this.onRenameHomeLink.bind(this)}>
                <p>This is some HTML code passed as a prop to the props.children of the Home class.
                    props.children is a reserved word</p>
            </Home>
        );
    }

    render() {
        return (
            <Router history={hashHistory}>
                <div className="container">
                    <div className="row">
                        <div className="col-xs-10 col-xs-offset-1">
                            <Header homeLink={this.state.homeLink}/>
                        </div>
                    </div>
                    <div className="row">
                        <div className="col-xs-10 col-xs-offset-1">
                            <Route exact path="/" component={(props, state, params) => this.setUpHomeProps()}/>
                            <Route path={"/home"} component={(props, state, params) => this.setUpHomeProps()}/>
                            <Route path={"/user/:id"} component={User}/>
                        </div>
                    </div>
                </div>
            </Router>
        );
    }
}

render(<App/>, window.document.getElementById("root"));