import React from "react";

export class Home extends React.Component {
    constructor(props) {
        super();
        this.state = {
            age: props.initialAge,
            homeLink: props.initialLink
        };

        console.log("Constructor called");
    }
    /*
    Tracking the component lifecycle here:
     */
    componentWillMount() {
        console.log("componentWillMount called");
    }
    componentDidMount() {
        console.log("componentDidMount called");
    }
    componentWillReceiveProps(nextProps) {
        console.log("componentWillReceiveProps called");
    }
    shouldComponentUpdate(nextProps, nextState) {
        console.log("shouldComponentUpdate called");
        return true;
    }
    componentWillUpdate(nextProps, nextState) {
        console.log("componentWillUpdate called");
    }
    componentDidUpdate(prevProps, prevState) {
        console.log("componentDidUpdate called");
    }
    componentWillUnmount() {
        console.log("componentWillUnmount called");
    }


    // increase the age. This will be called from the button below; in the onClick event we call this function by binding
    // the Home-classes' onMakeOlder function to the onClick event. Anotehr possibility is () => this.onMakeOlder()
    onMakeOlder() {
        // triggers re-rendering of the changed component
        // other fields of the state object won't be changed/deleted
        this.setState({
            age: this.state.age + 1
        });
    }
    
    renameHomeLink() {
        this.props.changeLink(this.state.homeLink);
    }

    onHandleChange(event) {
        this.setState({
            homeLink: event.target.value
        });
    }

    render() {
        // Component has props variable
        console.log(this.props);

        return (
            <div>
                <p>Hey a component</p>

                <p>User Name is { this.props.name } and age is {this.state.age}</p>
                <div>
                    <h4>Hobbies</h4>
                    <ul>
                        {this.props.user.hobbies.map((hobby, index) => <li key={ index }>{hobby}</li>)}
                    </ul>
                </div>
                <button className="btn btn-primary" onClick={this.onMakeOlder.bind(this)}>Make me older</button>
                <hr/>
                <button className="btn btn-default" onClick={this.props.functionCallback}>Call parent function</button>
                <hr/>
                <input type="text" value={this.state.homeLink} onChange={(event) => this.onHandleChange(event)}/>
                <button className="btn btn-default" onClick={this.renameHomeLink.bind(this)}>Change Header</button>
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
    functionCallback: React.PropTypes.func,
    initialLink: React.PropTypes.string,
    changeLink: React.PropTypes.func,

    children: React.PropTypes.element.isRequired
};