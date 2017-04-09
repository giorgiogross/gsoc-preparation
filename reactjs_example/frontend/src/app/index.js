import React from "react";
import { render } from "react-dom";

class App extends React.Component {
    render () {
        return (
            // only one parent element is allowed here
            // use className instead oof class; add some bootstrap here
            <div className="container">
                <div className="row">
                    <div className="col-xs-10 col-xs-offset1">
                        <h1>Hello!</h1>
                    </div>
                </div>
            </div>
        );
    }
}

render(<App/>, window.document.getElementById("root"));