const canvas = document.getElementById("canvas");
const ctx = canvas.getContext("2d");
const vertexRadius = 20;
const edgeWidth = 3;

const unvisTextColor = "#ffffff";
const unvisVertexColor = "#808080";//"#9b4dca";
const unvisEdgeColor = "#737373";//"#37474f";

const visTextColor = "#ffffff";
const visVertexColor = "#e91e63";//"#9b4dca";
const visEdgeColor = "#595959";//"#37474f";

// const visitedColor = "#e91e63";
const stackColor = "#2196f3";
const delay = 1000;

class Graph {
    constructor(vertices) {
        this.vertices = vertices;
        this.edges = [];
        for (let i = 0; i < vertices; i++) {
            this.edges.push([]);
        }
    }

    addEdge (u, v) {
        this.edges[u].push(v);
        this.edges[v].push(u);
    }

    dfs (start) {
        const visited = new Array(this.vertices).fill(false);
        const stack = [start];
        while (stack.length > 0) {
            const current = stack.pop();
            if (!visited[current]) {
                this.drawVertex(current, visitedColor);
                visited[current] = true;
                setTimeout(() => {
                    for (let i = 0; i < this.edges[current].length; i++) {
                        const neighbor = this.edges[current][i];
                        if (!visited[neighbor]) {
                            stack.push(neighbor);
                            this.drawEdge(current, neighbor, stackColor);
                        } else {
                            this.drawEdge(current, neighbor, visitedColor);
                        }
                    }
                    this.drawVertex(current, unvisVertexColor);
                }, delay);
            }
        }
    }

    drawGraph () {
        for (let i = 0; i < this.vertices; i++) {
            this.drawVertex(i, unvisVertexColor);
        }
        for (let i = 0; i < this.vertices; i++) {
            for (let j = 0; j < this.edges[i].length; j++) {
                const neighbor = this.edges[i][j];
                if (i < neighbor) {
                    this.drawEdge(i, neighbor, unvisEdgeColor);
                }
            }
        }
    }

    drawVertex (vertex, color) {
        console.log("drawVertex", vertex, color);
        ctx.fillStyle = color;
        ctx.beginPath();
        ctx.arc(this.getVertexX(vertex), this.getVertexY(vertex), vertexRadius, 0, 2 * Math.PI);
        ctx.fill();
        ctx.closePath();

        ctx.fillStyle = unvisTextColor;
        ctx.font = "25px Arial";
        ctx.textAlign = "center";
        ctx.textBaseline = "middle";
        ctx.fillText(vertex, this.getVertexX(vertex), this.getVertexY(vertex));
    }

    drawEdge (u, v, color) {
        console.log("drawEdge", u, v, color)
        ctx.strokeStyle = color;
        ctx.lineWidth = edgeWidth;
        ctx.beginPath();
        ctx.moveTo(this.getVertexX(u), this.getVertexY(u));
        ctx.lineTo(this.getVertexX(v), this.getVertexY(v));
        ctx.stroke();
        ctx.closePath();
    }

    getVertexX (vertex) {
        const cols = Math.ceil(Math.sqrt(this.vertices));
        const col = vertex % cols;
        return (canvas.width / cols) * (col + 0.5);
    }

    getVertexY (vertex) {
        const cols = Math.ceil(Math.sqrt(this.vertices));
        const row = Math.floor(vertex / cols);
        return (canvas.height / cols) * (row + 0.5);
    }
}

const graph = new Graph(4);
graph.addEdge(0, 1);
graph.addEdge(0, 2);
graph.addEdge(1, 3);
graph.addEdge(2, 3);

graph.drawGraph();

// graph.dfs(0);