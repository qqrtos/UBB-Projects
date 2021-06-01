export class Log {
    id: number;
    type: string;
    severity: string;
    date: Date;
    userId: number;
    text: string;

    constructor(id: number,  type: string, severity: string, date: Date, userId: number, text: string){
        this.id = id;
        this.type = type;
        this.severity = severity;
        this.date = date;
        this.userId = userId;
        this.text = text;
    }
}