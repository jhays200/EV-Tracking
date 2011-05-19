<%@ Page Language="C#" MasterPageFile="~/Telemetry.master" AutoEventWireup="true"
    CodeFile="About.aspx.cs" Inherits="_Default" Title="Untitled Page" %>

<asp:Content ID="Content1" ContentPlaceHolderID="head" runat="Server">
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="body" runat="Server">
    <div class="leftdiv">
        <h1>Inside</h1>
        <ul>
            <li><a href="#Purpose">Purpose</a></li>
            <li><a href="#Scope">Scope</a></li>
            <li><a href="#Definitions">Definitions</a></li>
            <li><a href="#System">System</a></li>
            <li><a href="#Technology">Technology</a></li>
            <li><a href="#Overview">Overview</a></li>
            <li><a href="#Description">Description</a></li>
        </ul>
    </div>
    <div class="content">
        <p>
            This is the introduction to the Velomobile system which covers the purpose, scope,
            definitions, acronyms, abbreviations, and references of the project.
        </p>
        <a name="Purpose"></a>
        <h2>
            Purpose</h2>
        <p>
            The purpose of the project is to provide an embedded controller for the Velomobile being               constructed by the mechanical engineering departments. The controller will control the power               assist and provide a quick dashboard display for Velomobile operators including information               such as speed, average speed, time, and battery levels. Also part of our project is the dynamic               telemetry web site which will display current and historical telemetry data via our web               presence. Data will be displayed via graphs of sensor readings, or maps of routes.
        </p>
        <a name="Scope"></a>
        <h2>
            Scope</h2>
        <p>
             The scope of this project encompasses the design and implementation of both the embedded               controller (power assist control schemes, heads up systems conditions) and the web based               telemetry system (GPS tracking, data acquisition/review). These two systems are our concern;               the design, implementation, and functionality of the velomobile are out of our control. This               document will be the “contract” used to determine our success at the end of the project. All               requirements listed here will be completed in full by the end of spring quarter.
        </p>
        
        <a name="Definitions"></a>
        <h2>
            Definitions, Acronyms and Abbreviations</h2>
        <p>
            This section will act as our data dictionary to aid users in reading the document.
            It will hopefully describe all terms, acronyms, and abbreviations used in this paper.
        </p>
        
        <a name="System"></a>
        <h3>
            System Related</h3>
        <ul>
            <li>Velomobile – Recumbent Tricycle</li>
            <li>Telemetry Web System – Web site, for storing/display telemetry data </li>
        </ul>
        
        <a name="Technology"></a>
        <h3>
            Technology Related</h3>
        <ul>
            <li>CSS – Cascading style sheets</li>
            <li>ASP – Active Server Pages</li>
            <li>C# – Microsoft Programming Language</li>
            <li>C – General Programming Language (Used on Embedded Controller) </li>
            <li>XML – Extensible Markup Language</li>
            <li>HTML – Hyper text markup language </li>
        </ul>
        <h2>
            References</h2>
            
        <a name="Overview"></a>
        <h2>
            Overview</h2>
        <p>
            The purpose of this document is to provide an in depth look at our system requirements, system               architecture, and other documentation relevant to the project. By the end of the document the               average reader should have a clear understanding of the system we are building.
        </p>
        
        <a name="Description"></a>
        <h1>
            Overall Description</h1>
        <p>
            The system we are developing can be broken down into two different pieces. The first piece               being the embedded controller for the velomobile. The second being the telemetry system for               the velomobile and other devices. The embedded controller will perform the mathematical               algorithms needed to control the electric power assist. Based on the power the user puts               into the               velomobile through peddling, they will be able to pull an assist through the electric motor that               will be proportional to the power they put in. The embedded controller will also display basic               telemetry data such as current speed, average speed, time, and battery levels. This data will be               streamed to the telemetry web system we are developing. The telemetry web system will accept               telemetry data dynamically from devices according to predefined XML formats and store it in               the database. It will then allow users to view real time and historical telemetry data.</p>
    </div>
</asp:Content>
