import React from "react";
import { BrowserRouter as Router } from "react-router-dom";

export class User extends React.Component {

    onGoHome() {
        this.props.history.push("/home")
    }

    render() {
        return (
            <div>
                <h1>User Page</h1>
                <p>User ID : {this.props.match.params.id}</p>
                <button className="btn btn-primary" onClick={() => this.onGoHome()}>Homedihome</button>
            </div>
        );
    }
}

User.propTypes = {};