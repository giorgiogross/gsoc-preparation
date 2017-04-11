import React from "react";
import {Link} from "react-router-dom";

// sate-less component which can only get some props but will never change its state from within itself
export const Header = (props) => {
    return (
        <nav className="navbar navbar-default">
            <div className="container">
                <div className="navbar-header">
                    <ul className="nav navbar-nav">
                        <li><Link to={"/home"}>{props.homeLink}</Link></li>
                        <li><Link to={"/user/4"}>User</Link></li>
                    </ul>
                </div>
            </div>
        </nav>
    );
};