import java.awt.*;
import java.awt.image.BufferedImage;

/**
	Esta classe representa os jogadores (players) do jogo. A classe principal do jogo
	instancia dois objetos deste tipo quando a execução é iniciada.
*/
public class Player implements ISolid {
	private double direction;
	private double cx, cy, width, height, speed;
	private Color color;
	private String id; 
	private BufferedImage img; 
	private long death_time = -1;
	private long ultimo_shot = -1;
	private boolean dead = false;

	/**
		Construtor da classe Player.

		@param cx coordenada x da posição inicial do player (centro do retângulo que o representa).
		@param cy coordenada y da posição inicial do player (centro do retângulo que o representa).
		@param width largura do retângulo que representa o player.
		@param height altura do retângulo que representa o player.
		@param angle direção apontada pelo player
		@param sprite gráfico do player
		@param color cor do player.
		@param id uma string que identifica o player
		@param speed velocidade do movimento do player.
	*/
	public Player(double cx, double cy, double width, double height, double angle, BufferedImage sprite, Color color, String id, double speed){
		this.cx = cx;
		this.cy = cy;
		this.width = width;
		this.height = height;
		this.color = color;
		this.id = id;
		this.direction = angle;
		this.speed = speed;
		this.img = sprite;
	}

	/**
		Método chamado sempre que o player precisa ser (re)desenhado.
	*/
	public void draw(){
		GameLib.setColor(color);

		if (isDead()) {
			long now = System.currentTimeMillis();
			GameLib.drawImage(img, cx, cy, direction + now % 60 * 60, width / img.getWidth());
			return;
		}

		GameLib.drawImage(img, cx, cy, direction, width / img.getWidth());
	}

	/**
		Método chamado quando se deseja mover para a frente na direção atual. 
		Este método é chamado sempre que a tecla associada à ação 
		de mover o player para frente estiver pressionada.

		@param delta quantidade de milissegundos que se passou entre o ciclo anterior de atualização do jogo e o atual.
	*/
	public void moveForwards(long delta){
		this.cx += Math.cos(Math.toRadians(direction)) * (speed * delta);
		this.cy += Math.sin(Math.toRadians(direction)) * (speed * delta);
	} 

	/**
		Método chamado quando se deseja mover o player para trás na direção atual. 
		Este método é chamado sempre que a tecla associada à ação 
		de mover o player para trás estiver pressionada.

		@param delta quantidade de milissegundos que se passou entre o ciclo anterior de atualização do jogo e o atual.
	*/
	public void moveBackwards(long delta){
		this.cx -= Math.cos(Math.toRadians(direction)) * (speed * delta);
		this.cy -= Math.sin(Math.toRadians(direction)) * (speed * delta);
	} 

	/**
		Método chamado quando se deseja girar o player para a esquerda (sentido anti-horário). 
		Este método é chamado sempre que a tecla associada à ação 
		de rotacionar o player à esquerda estiver pressionada.

		@param delta quantidade de milissegundos que se passou entre o ciclo anterior de atualização do jogo e o atual.
	 */
	public void rotateLeft(long delta) {
		this.direction -= delta * speed;
	} 

	/**
		Método chamado quando se deseja girar o player para a direita (sentido horário). 
		Este método é chamado sempre que a tecla associada à ação 
		de rotacionar o player à direita estiver pressionada.

		@param delta quantidade de milissegundos que se passou entre o ciclo anterior de atualização do jogo e o atual.
	 */
	public void rotateRight(long delta) {
		this.direction += delta * speed;
	} 

	/**
	 * Retorna se o jogador pode realizar um disparo ou não. Chamado sempre que a ação de disparar
	 * desse player for acionada.
	 */
	public boolean canFire() {
		if (!isDead() && System.currentTimeMillis() - ultimo_shot >= 1000) return true;
		return false;
	} 

	/**
	 * Cria um disparo vindo desse player na mesma direção apontada pelo player.
	 * Esse método cria o disparo e o adiciona ao jogo.
	 */
	public void fire() {
		if (canFire()) {
			Shot novo_shot = new Shot(this, cx, cy, 4.0, direction, 0.2);
			Combat.addShot(novo_shot);
			this.ultimo_shot = System.currentTimeMillis();
		}
	} 

	/**
	 * Retorna se o player acabou de ser destruído. Enquanto o player estiver destruído, ele não
	 * poderá ser danificado novamente.
	 */
	public boolean isDead() {
		return dead;
	} 

	/**
	 * Chamado sempre que o player for destruído com um disparo. 
	 */
	public void die() {
		if (!isDead()) {
			this.dead = true;
			this.death_time = System.currentTimeMillis();
			draw();
			double new_spawn[] = Map.getRandomRespawn();
			setPosition(new_spawn[0], new_spawn[1]);
			this.dead = false;
			this.death_time = -1;
		}
	} 

	/**
		Método que devolve a string de identificação do player.
		@return a String de identificação.
	*/
	public String getId() { 
		return id; 
	} 

	/**
	 * Teleporta o player para essa coordenada do mapa.
	 */
	public void setPosition(double cx, double cy) {
		this.cx = cx;
		this.cy = cy;
	} 

	/**
		Método que devolve a largura do retângulo que representa o player.
		@return um double com o valor da largura.
	*/
	public double getWidth() { 
		return width; 
	} 

	/**
		Método que devolve a altura do retângulo que representa o player.
		@return um double com o valor da altura.
	*/
	public double getHeight() { 
		return height;
	} 

	/**
		Método que devolve a coordenada x do centro do retângulo que representa o player.
		@return o valor double da coordenada x.
	*/
	public double getCx() { 
		return cx;
	} 

	/**
		Método que devolve a coordenada y do centro do retângulo que representa o player.
		@return o valor double da coordenada y.
	*/
	public double getCy() { 
		return cy;
	} 

	/**
	 * Obtém a cor do player.
	 */
	public Color getColor() {
		return color;
	} 
}

