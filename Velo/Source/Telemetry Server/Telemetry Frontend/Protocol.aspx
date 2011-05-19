<%@ Page Language="C#" MasterPageFile="~/Telemetry.master" AutoEventWireup="true"
    CodeFile="Protocol.aspx.cs" Inherits="_Default" Title="Untitled Page" %>

<asp:Content ID="Content1" ContentPlaceHolderID="head" runat="Server">
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="body" runat="Server">
    <div class="leftdiv">
        <h1>Inside</h1>
        <ul>
            <li><a href="Protocol.aspx">Protocol</a></li>
            <li><a href="Protocol.Live.aspx">Live Parser</a></li>
        </ul>
    </div>
    <div class="content">
        <h1>XML-RPC Specification</h1>
		<b>Tue, January 19, 2010; by Shawn McGinnis.</b>
		<p>This specification documents the XML-meTRICS protocol.<br/>
		This page provides all the information needed to implement this portocol.</h2>
        <h2>Request</h2>
        <p>
			POST HTTP<br/>
			Host: trics.us<br/>
			Content-Type: metric/xml<br/>	
		</p>
        <p>
			POST HTTP<br/>
			Host: trics.us<br/>
			Content-Type: metric/image<br/>	
		</p>
        <h2>Setup</h2>
        <p>
            [ Fields ]<br />
            { Optional (Default) }<br />
            &lt;[DEVICE] {{whitespace}|{w}=&quot;[(true)SEE DATATYPES:Bool]&quot;}&gt;<br />
            &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &lt;[ELEMENT] {type=&quot;[SEE DATATYPES]&quot;}
            {display=&quot;[SEE DISPLAYS]&quot;}&gt;[DATA]&lt;/[ELEMENT]&gt;<br />
            &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &lt;[ELEMENT]...&lt;/[ELEMENT]&gt;<br />
            &lt;/[DEVICE]&gt;</p>
        <h2>Stream</h2>
        <p>
            [ Fields ]<br />
            { Optional }<br />
            {< ?xml version="1.0" encoding="[SEE DATATYPES:Encoding]" ? >}<br />
                        &lt;[DEVICE] {{{t}|{timestamp}=&quot;[TIMESTAMP]&quot;}|{{d}|{datetime}=&quot;[DATETIME]&quot;}}&gt;<br />
            &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &lt;[ELEMENT] {{{t}|{timestamp}=&quot;[TIMESTAMP]&quot;}|{{d}|{datetime}=&quot;[DATETIME]&quot;}}
            {{p|process}=&quot;[SEE PROCESSING]&quot;}&gt;[DATA]&lt;/[ELEMENT]&gt;<br />
            &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &lt;[ELEMENT]...&lt;/[ELEMENT]&gt;<br />
            &lt;/[DEVICE]&gt;
        </p>
        <h2>
            Data Types
        </h2>
        <ul>
            <li>Bool Types: 
                <ul>
                    <li>True | true</li>
                    <li>False | false</li>
                </ul>
            </li>
            <li>Coordinates Types:<ul>
                <li>DMS - Degrees:Minutes:Seconds
                (49°30&#39;00&quot;, 123°30&#39;00&quot;W)</li>
                <li>DM - Degrees:Decimal Minutes (49°30.0&#39;,
                -123°30.0&#39;), (49d30.0m,-123d30.0&#39;) </li>
                <li>DD - Decimal Degrees (49.5000,-123.5000)
                </li>
                </ul>
            </li>
            <li>Encoding Types: 
                <ul>
                    <li>UTF-8</li>
                    <li>UTF-18</li>
                    <li>ISO-8859-1</li>
                </ul>
            </li>
            <li>Data<ul>
                <li>Stipulations: 
                    <ul>
                        <li>Requires that the xml
                stream header allow datatype</li>
                    </ul>
                </li>
                <li>Types: 
                    <ul>
                        <li>Base64</li>
                        <li>ASCII</li>
                        <li>UTF-8</li>
                    </ul>
                </li>
                </ul>
            </li>
        </ul>
        <h2>
            Displays</h2>
        <ul>
            <li>GoogleMap</li>
            <li>Accelerometer</li>
            <li>Compass</li>
        </ul>
                <h2>
                    Processing</h2><ul>
            <li>Numerical.Bounds</li>
            <li>Numerical.Average</li>
            <li>Mapping.Path.Distance</li>
            <li>Mapping.Path.Route</li>
            <li>Twitter.Post</li>
            <li>[Device Name].[Element ID]</li></ul>
            
    </div>
</asp:Content>
