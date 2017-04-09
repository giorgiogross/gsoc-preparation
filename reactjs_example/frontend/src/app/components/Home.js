import React from "react";

export class Home extends React.Component {
    render() {
        // Component has props variable
        console.log(this.props);

        return (
            <div>
                <p>Hey a component</p>

                <p>User Name is { this.props.name } and age is {this.props.age}; Hobbies:</p>
                <div>
                    <h4>Hobbies</h4>
                    <ul>
                        {this.props.user.hobbies.map((hobby, index) => <li key={ index }>{hobby}</li>)}
                    </ul>
                </div>
                <hr/>
                {this.props.children}
            </div>
        );
    }
}

// make sure that other classes pass the right prop types
Home.propTypes = {
    name: React.PropTypes.string,
    age: React.PropTypes.number,
    user: React.PropTypes.object,

    children: React.PropTypes.element.isRequired
};